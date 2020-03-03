#ifndef DOCCONTROLLER_H
#define DOCCONTROLLER_H

#include <QObject>
#include "subdata.h"

class MainWindow;
class QXmlStreamWriter;

struct CellData
{
    QString m_Line;
    QString m_Size;
    bool    m_IsBold;

    CellData(QString Line, QString Size, bool IsBold) : m_Line(Line), m_Size(Size), m_IsBold(IsBold) {};
};

// Will handle convertation to .doc formate
class CDocController: public QObject
{
public:
    void SetMainWindow(MainWindow* MainWindow);

private:
    void StartElement(QXmlStreamWriter& XMLWriter, const QString& Element);
    void EndElement(QXmlStreamWriter& XMLWriter);
    void EndAllElements(QXmlStreamWriter& XMLWriter);

    void InsertRow(QXmlStreamWriter& XMLWriter, const std::vector<CellData>& CellDataElements);
    void InsertColumn(QXmlStreamWriter& XMLWriter, const CellData& CellDataElement);

public slots:
    void ConvertSubDataToDoc(const QString& FileName, const std::vector<CSubData>& SubData);

private:
    MainWindow* m_MainWindow;
    quint32     m_OpenElements = 0;
};

#endif // DOCCONTROLLER_H
