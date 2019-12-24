#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "doccontroller.h"
#include "subcontroller.h"
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CharacterData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    void OnFileNameReceived(const QString&);

private slots:
    void OnBrowseClicked();

private:
    Ui::MainWindow *ui;

    std::set<CharacterData> m_Characters;
    SubController           m_SubController;
    DocController           m_DocController;

};
#endif // MAINWINDOW_H
