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
    void OnFileNameReceived(const QString&, SubPauseInfo);
    void OnExportRequired(const QString&, const QString&, const std::vector<CSubData>& subData);

private slots:
    void OnBrowseClicked();
    void OnExportToDocClicked();
    void OnNamesTableCellClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    std::set<CCharacterData> _characters;
    CSubController           _subDataController;
    CDocController           _docController;

};
#endif // MAINWINDOW_H
