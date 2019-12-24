#ifndef SUBCONTROLLER_H
#define SUBCONTROLLER_H

#include <QObject>
#include "subdata.h"
#include <vector>

class MainWindow;

// Will handle parsing part and storing part
class SubController: public QObject
{
public:
    void SetMainWindow(MainWindow* MainWindow);

public slots:
    void ExtractDataFromFile(const QString& Filename);

private:
    std::vector<SubData> m_Sub;
    MainWindow*          m_MainWindow;
};

#endif // SUBCONTROLLER_H
