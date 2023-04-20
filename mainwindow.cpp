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
    _subDataController.SetMainWindow(this);
    _docController.SetMainWindow(this);

    connect(this, &MainWindow::OnFileNameReceived, &_subDataController, &CSubController::ExtractDataFromFile);
    connect(this, &MainWindow::OnExportRequired, &_docController, &CDocController::ConvertSubDataToDoc);
}

MainWindow::~MainWindow()
{
    disconnect(this, &MainWindow::OnFileNameReceived, &_subDataController, &CSubController::ExtractDataFromFile);
    disconnect(this, &MainWindow::OnExportRequired, &_docController, &CDocController::ConvertSubDataToDoc);
    delete ui;
}

CCharacterData *MainWindow::GetCharacter(QString name)
{
    std::pair<std::set<CCharacterData>::iterator, bool> result = _characters.insert(CCharacterData(name));

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
    for(auto& character : _characters)
    {
        qDebug() << "character._name " << character._name << Qt::endl;

        ui->NamesTable->insertRow(row);
        ui->NamesTable->setItem(row, 0, new QTableWidgetItem(QString::number(row)));
        ui->NamesTable->setItem(row, 1, new QTableWidgetItem(character._name));
        ui->NamesTable->setItem(row, 2, new QTableWidgetItem(character._gender == Gender::male ? "m" : "f"));

        ++row;
    }

    // Ресайзим колонки по содержимому
     ui->NamesTable->resizeColumnsToContents();
}

void MainWindow::OnBrowseClicked()
{
    const QString fileName = Utils::GetFileName(ui->BrowseLine->text());

    if (!fileName.size())
        return;

    ui->BrowseLine->setText(fileName);

    emit OnFileNameReceived(fileName, ui->EnablePause->isChecked());
}

void MainWindow::OnExportToDocClicked()
{
    QString fileName = Utils::GetSaveFileName(ui->ExportToDocLine->text());

    if (!fileName.size())
        return;

    ui->ExportToDocLine->setText(fileName);

    emit OnExportRequired(fileName, ui->DocNameLine->text(), _subDataController.GetSubData());
}

void MainWindow::OnNamesTableCellClicked(int row, int column)
{
    if (column != 2)
        return;

    std::set<CCharacterData>::iterator it = _characters.begin();
    std::advance(it, row);

    it->_gender = (*it)._gender == Gender::male ? Gender::female : Gender::male;
    ui->NamesTable->setItem(row, 2, new QTableWidgetItem(it->_gender == Gender::male ? "m" : "f"));
}
