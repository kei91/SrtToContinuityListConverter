#ifndef DOCCONTROLLER_H
#define DOCCONTROLLER_H

#include <QObject>
#include "subdata.h"

class MainWindow;
class QXmlStreamWriter;

struct CellData
{
    QString _line;
    QString _size;
    bool    _isBold;

    CellData(QString line, QString size, bool isBold) : _line(line), _size(size), _isBold(isBold) {};
};

// Will handle convertation to .doc formate
class CDocController: public QObject
{
public:
    void SetMainWindow(MainWindow* MainWindow);

public slots:
    void ConvertSubDataToDoc(const QString& fileName, const QString& strTitle, const std::vector<CSubData>& subData);

private:
    MainWindow* _mainWindow;
    quint32     m_OpenElements = 0;
};

#endif // DOCCONTROLLER_H
