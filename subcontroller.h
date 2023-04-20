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
    void SetMainWindow(MainWindow* mainWindow);
    const std::vector<CSubData>& GetSubData() const;

public slots:
    void ExtractDataFromFile(const QString& filename, bool pauseEnabled);

private:
    std::vector<CSubData> _subData;
    MainWindow*           _mainWindow;
};

#endif // SUBCONTROLLER_H
