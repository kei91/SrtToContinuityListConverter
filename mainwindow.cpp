#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "characterdata.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_SubController.SetMainWindow(this);
    m_DocController.SetMainWindow(this);

    connect(this, &MainWindow::OnFileNameReceived, &m_SubController, &SubController::ExtractDataFromFile);
}

MainWindow::~MainWindow()
{
    disconnect(this, &MainWindow::OnFileNameReceived, &m_SubController, &SubController::ExtractDataFromFile);
    delete ui;
}

void MainWindow::OnBrowseClicked()
{
    const QString fileName = Utils::GetFileName();

    if (!fileName.count())
        return;

    emit OnFileNameReceived(fileName);
}
