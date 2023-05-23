#ifndef SUBCONTROLLER_H
#define SUBCONTROLLER_H

#include <QObject>
#include "subdata.h"
#include <vector>

class MainWindow;

struct SubPauseInfo {
  bool pauseEnabled = false;
  int smallPauseStart = 0;
  int smallPauseEnd = 0;
  int bigPauseStart = 0;

  SubPauseInfo(bool _pauseEnabled, int _smallPauseStart, int _smallPauseEnd, int _bigPauseStart)
    : pauseEnabled(_pauseEnabled)
    , smallPauseStart(_smallPauseStart)
    , smallPauseEnd(_smallPauseEnd)
    , bigPauseStart(_bigPauseStart)
  {}
};

// Will handle parsing part and storing part
class CSubController: public QObject
{
public:
    void SetMainWindow(MainWindow* mainWindow);
    const std::vector<CSubData>& GetSubData() const;

public slots:
    void ExtractDataFromFile(const QString& filename, SubPauseInfo pauseInfo);

private:
    std::vector<CSubData> _subData;
    MainWindow*           _mainWindow;
};

#endif // SUBCONTROLLER_H
