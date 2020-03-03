#ifndef SUBCONTROLLER_H
#define SUBCONTROLLER_H

#include <QObject>
#include "subdata.h"
#include <vector>

class MainWindow;

// Will handle parsing part and storing part
class CSubController: public QObject
{
public:
    void SetMainWindow(MainWindow* MainWindow);
    const std::vector<CSubData>& GetSubData() const;

public slots:
    void ExtractDataFromFile(const QString& Filename);

private:
    std::vector<CSubData> m_Sub;
    MainWindow*           m_MainWindow;
};

#endif // SUBCONTROLLER_H
