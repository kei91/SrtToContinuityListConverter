#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "characterdata.h"
#include <QDebug>
#include <set>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_SubController.SetMainWindow(this);
    m_DocController.SetMainWindow(this);

    connect(this, &MainWindow::OnFileNameReceived, &m_SubController, &CSubController::ExtractDataFromFile);
    connect(this, &MainWindow::OnExportRequired, &m_DocController, &CDocController::ConvertSubDataToDoc);
}

MainWindow::~MainWindow()
{
    disconnect(this, &MainWindow::OnFileNameReceived, &m_SubController, &CSubController::ExtractDataFromFile);
    disconnect(this, &MainWindow::OnExportRequired, &m_DocController, &CDocController::ConvertSubDataToDoc);
    delete ui;
}

CCharacterData *MainWindow::GetCharacter(QString name)
{
    std::pair<std::set<CCharacterData>::iterator, bool> result = m_Characters.insert(CCharacterData(name));

    return const_cast<CCharacterData *>(&(*result.first));
}

void MainWindow::UpdateTable()
{
    ui->NamesTable->setColumnCount(3);
    ui->NamesTable->setShowGrid(true);
    ui->NamesTable->setHorizontalHeaderLabels(QStringList({"№", "Имя", "Гендер"}));
    ui->NamesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* header = ui->NamesTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    quint8 row = 0;
    for(auto character : m_Characters)
    {
        qDebug() << "character.m_Name " << character.m_Name << endl;

        ui->NamesTable->insertRow(row);
        ui->NamesTable->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
        ui->NamesTable->setItem(row, 1, new QTableWidgetItem(character.m_Name));
        ui->NamesTable->setItem(row, 2, new QTableWidgetItem(character.m_Gender == Gender::male ? "m" : "f"));

        ++row;
    }

    // Ресайзим колонки по содержимому
     ui->NamesTable->resizeColumnsToContents();
}

void MainWindow::OnBrowseClicked()
{
    const QString fileName = Utils::GetFileName(ui->BrowseLine->text());

    if (!fileName.count())
        return;

    ui->BrowseLine->setText(fileName);

    emit OnFileNameReceived(fileName);
}

void MainWindow::OnExportToDocClicked()
{
    QString fileName = Utils::GetSaveFileName(ui->ExportToDocLine->text());

    if (!fileName.count())
        return;

    ui->ExportToDocLine->setText(fileName);

    emit OnExportRequired(fileName, ui->DocNameLine->text(), m_SubController.GetSubData());
}

void MainWindow::OnNamesTableCellClicked(int row, int column)
{
    if (column != 2)
        return;

    std::set<CCharacterData>::iterator it = m_Characters.begin();
    std::advance(it, row);

    it->m_Gender = (*it).m_Gender == Gender::male ? Gender::female : Gender::male;
    ui->NamesTable->setItem(row, 2, new QTableWidgetItem(it->m_Gender == Gender::male ? "m" : "f"));
}
