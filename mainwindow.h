#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "doccontroller.h"
#include "subcontroller.h"
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CCharacterData;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    CCharacterData *GetCharacter(QString name);

    void UpdateTable();

signals:
    void OnFileNameReceived(const QString&);
    void OnExportRequired(const QString&, const QString&, const std::vector<CSubData>& SubData);

private slots:
    void OnBrowseClicked();
    void OnExportToDocClicked();
    void OnNamesTableCellClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    std::set<CCharacterData> m_Characters;
    CSubController           m_SubController;
    CDocController           m_DocController;

};
#endif // MAINWINDOW_H
