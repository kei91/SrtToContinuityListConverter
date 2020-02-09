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

    connect(this, &MainWindow::OnFileNameReceived, &m_SubController, &SubController::ExtractDataFromFile);
}

MainWindow::~MainWindow()
{
    disconnect(this, &MainWindow::OnFileNameReceived, &m_SubController, &SubController::ExtractDataFromFile);
    delete ui;
}

CharacterData *MainWindow::GetCharacter(QString name)
{
    std::pair<std::set<CharacterData>::iterator, bool> result;
    m_Characters.insert(CharacterData(name));

    return const_cast<CharacterData *>(&(*result.first));
}

void MainWindow::OnBrowseClicked()
{
    const QString fileName = Utils::GetFileName();

    if (!fileName.count())
        return;

    emit OnFileNameReceived(fileName);
}
