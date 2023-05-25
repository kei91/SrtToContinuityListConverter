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

struct FemaleLinesStyle {
    bool isBold;
    bool isUnderline;
    bool isItalic;

    FemaleLinesStyle(bool _isBold, bool _isUnderline, bool _isItalic)
        : isBold(_isBold)
        , isUnderline(_isUnderline)
        , isItalic(_isItalic)
    {}
};

// Will handle convertation to .doc formate
class CDocController: public QObject
{
public:
    void SetMainWindow(MainWindow* MainWindow);

public slots:
    void ConvertSubDataToDoc(const QString& fileName, const QString& strTitle, const std::vector<CSubData>& subData, FemaleLinesStyle style, bool useUnderline);

private:
    MainWindow* _mainWindow;
    quint32     m_OpenElements = 0;
};

#endif // DOCCONTROLLER_H
