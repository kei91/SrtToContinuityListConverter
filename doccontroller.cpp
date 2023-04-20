#include "doccontroller.h"
#include "mainwindow.h"
#include "characterdata.h"
#include <QDebug>

#include <QFile>
#include <QTextStream>

#include <QXmlStreamWriter>
#include <QMessageBox>

void CDocController::SetMainWindow(MainWindow* MainWindow)
{
    _mainWindow = MainWindow;
}

void CDocController::ConvertSubDataToDoc(const QString& fileName, const QString& strTitle, const std::vector<CSubData>& subData)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument("1.0");

    StartElement(xmlWriter, "w:wordDocument");
    xmlWriter.writeAttribute("xmlns:w", "http://schemas.microsoft.com/office/word/2003/wordml");
    StartElement(xmlWriter, "w:body");

    StartElement(xmlWriter, "w:p");
    xmlWriter.writeAttribute("xmlns:fo", "urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0");
    StartElement(xmlWriter, "w:r");
    StartElement(xmlWriter, "w:t");
    xmlWriter.writeCharacters(strTitle);
    EndElement(xmlWriter);
    EndElement(xmlWriter);
    EndElement(xmlWriter);

// table
    StartElement(xmlWriter, "w:tbl");

    StartElement(xmlWriter, "w:tblPr");

    StartElement(xmlWriter, "w:tblStyle");
    xmlWriter.writeAttribute("w:val", "Table1");
    EndElement(xmlWriter);

    StartElement(xmlWriter, "w:tblW");
    xmlWriter.writeAttribute("w:type", "auto");
    EndElement(xmlWriter);

    StartElement(xmlWriter, "w:tblInd");
    xmlWriter.writeAttribute("w:type", "auto");
    EndElement(xmlWriter);

    StartElement(xmlWriter, "w:jc");
    xmlWriter.writeAttribute("w:val", "left");
    EndElement(xmlWriter);

    EndElement(xmlWriter); // w:tblPr

    StartElement(xmlWriter, "w:tblGrid");

    StartElement(xmlWriter, "w:gridCol");
    xmlWriter.writeAttribute("w:w", "1698");
    EndElement(xmlWriter); // w:gridCol

    StartElement(xmlWriter, "w:gridCol");
    xmlWriter.writeAttribute("w:w", "1755");
    EndElement(xmlWriter); // w:gridCol

    StartElement(xmlWriter, "w:gridCol");
    xmlWriter.writeAttribute("w:w", "6897");
    EndElement(xmlWriter); // w:gridCol

    EndElement(xmlWriter); // w:tblGrid

    std::vector<CellData> CellDatasHeadLine;
    CellDatasHeadLine.push_back(CellData("Тайм-код", "1698", true));
    CellDatasHeadLine.push_back(CellData("Герои", "1755", true));
    CellDatasHeadLine.push_back(CellData("Реплики", "6897", true));

    InsertRow(xmlWriter, CellDatasHeadLine);

    for (const CSubData& data : subData)
    {
        std::vector<CellData> CellDataElement;

        qDebug() << "SubData in doc" << Qt::endl;
        qDebug() << "time" << data._startTime.toString("hh::mm::ss") << Qt::endl;
        qDebug() << "name" << data._character->_name << Qt::endl;
        qDebug() << "line" << data._line << Qt::endl;

        CellDataElement.push_back(CellData(data._startTime.toString("hh:mm:ss"), "1698", false));
        CellDataElement.push_back(CellData(data._character->_name, "1755", data._character->_gender == Gender::female));
        CellDataElement.push_back(CellData(data._line, "6897", false));

        InsertRow(xmlWriter, CellDataElement);
    }

    EndElement(xmlWriter); // w:tbl

    StartElement(xmlWriter, "w:sectPr");
    EndAllElements(xmlWriter);
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    QMessageBox msgBox;
    msgBox.setWindowTitle("Выгрузка в doc");
    msgBox.setText("Выгрузка в doc завершена");
    msgBox.exec();
}

void CDocController::StartElement(QXmlStreamWriter& XMLWriter, const QString& Element)
{
    XMLWriter.writeStartElement(Element);
    ++m_OpenElements;
}

void CDocController::EndElement(QXmlStreamWriter& XMLWriter)
{
    XMLWriter.writeEndElement();
    --m_OpenElements;
}

void CDocController::EndAllElements(QXmlStreamWriter& XMLWriter)
{
    while(m_OpenElements > 0)
    {
        EndElement(XMLWriter);
    }
}

void CDocController::InsertRow(QXmlStreamWriter& XMLWriter, const std::vector<CellData>& cellDataElements)
{
    StartElement(XMLWriter, "w:tr");

    StartElement(XMLWriter, "w:trPr");
    EndElement(XMLWriter);

    for (const CellData& CellDataElement : cellDataElements)
        InsertColumn(XMLWriter, CellDataElement);

    EndElement(XMLWriter); // w:tr
}

void CDocController::InsertColumn(QXmlStreamWriter& XMLWriter, const CellData& cellDataElement)
{
    StartElement(XMLWriter, "w:tc");
    StartElement(XMLWriter, "w:tcPr");
    StartElement(XMLWriter, "w:tcW");
    XMLWriter.writeAttribute("w:type", "dxa");
    XMLWriter.writeAttribute("w:w", cellDataElement._size);
    EndElement(XMLWriter); // w:tcW
    StartElement(XMLWriter, "w:tcBorders");

    const QString orientations[4] = {"w:top", "w:bottom", "w:left", "w:right"};
    for (const QString& orientation : orientations)
    {
        StartElement(XMLWriter, orientation);
        XMLWriter.writeAttribute("w:val", "single");
        XMLWriter.writeAttribute("w:sz", "0");
        XMLWriter.writeAttribute("w:color", "000000");
        EndElement(XMLWriter);
    }

    EndElement(XMLWriter); // tcBorders
    EndElement(XMLWriter); // w:tcPr

    StartElement(XMLWriter, "w:p");
    StartElement(XMLWriter, "w:pPr");
    StartElement(XMLWriter, "w:pStyle");
    XMLWriter.writeAttribute("w:val", "P4");
    EndElement(XMLWriter); // w:pStyle
    EndElement(XMLWriter); // w:pPr
    StartElement(XMLWriter, "w:r");

    if (cellDataElement._isBold)
    {
        StartElement(XMLWriter, "w:rPr");
        StartElement(XMLWriter, "w:b");
        EndElement(XMLWriter); // w:b
        EndElement(XMLWriter); // w:rPr
    }

    StartElement(XMLWriter, "w:t");
    XMLWriter.writeCharacters(cellDataElement._line);
    EndElement(XMLWriter); // w:t
    EndElement(XMLWriter); // w:r
    EndElement(XMLWriter); // w:p

    EndElement(XMLWriter); // w:tc
}
