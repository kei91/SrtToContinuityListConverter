#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "characterdata.h"
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

void MainWindow::OnBrowseClicked()
{
    const QString fileName = Utils::GetFileName();

    if (!fileName.count())
        return;

    emit OnFileNameReceived(fileName);
}

void MainWindow::OnExportToDocClicked()
{
    QString fileName = Utils::GetSaveFileName();

    if (!fileName.count())
        return;

    emit OnExportRequired(fileName, m_SubController.GetSubData());
}
