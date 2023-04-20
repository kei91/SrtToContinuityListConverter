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
    m_MainWindow = MainWindow;
}

void CDocController::ConvertSubDataToDoc(const QString& FileName, const QString& StrTitle, const std::vector<CSubData>& SubData)
{
    QFile file(FileName);
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
    xmlWriter.writeCharacters(StrTitle);
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

    for (const CSubData& data : SubData)
    {
        std::vector<CellData> CellDataElement;

        qDebug() << "SubData in doc" << Qt::endl;
        qDebug() << "time" << data.m_StartTime.toString("hh::mm::ss") << Qt::endl;
        qDebug() << "name" << data.m_Character->m_Name << Qt::endl;
        qDebug() << "line" << data.m_Line << Qt::endl;

        CellDataElement.push_back(CellData(data.m_StartTime.toString("hh:mm:ss"), "1698", false));
        CellDataElement.push_back(CellData(data.m_Character->m_Name, "1755", data.m_Character->m_Gender == Gender::female));
        CellDataElement.push_back(CellData(data.m_Line, "6897", false));

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

void CDocController::InsertRow(QXmlStreamWriter& XMLWriter, const std::vector<CellData>& CellDataElements)
{
    StartElement(XMLWriter, "w:tr");

    StartElement(XMLWriter, "w:trPr");
    EndElement(XMLWriter);

    for (const CellData& CellDataElement : CellDataElements)
        InsertColumn(XMLWriter, CellDataElement);

    EndElement(XMLWriter); // w:tr
}

void CDocController::InsertColumn(QXmlStreamWriter& XMLWriter, const CellData& CellDataElement)
{
    StartElement(XMLWriter, "w:tc");
    StartElement(XMLWriter, "w:tcPr");
    StartElement(XMLWriter, "w:tcW");
    XMLWriter.writeAttribute("w:type", "dxa");
    XMLWriter.writeAttribute("w:w", CellDataElement.m_Size);
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

    if (CellDataElement.m_IsBold)
    {
        StartElement(XMLWriter, "w:rPr");
        StartElement(XMLWriter, "w:b");
        EndElement(XMLWriter); // w:b
        EndElement(XMLWriter); // w:rPr
    }

    StartElement(XMLWriter, "w:t");
    XMLWriter.writeCharacters(CellDataElement.m_Line);
    EndElement(XMLWriter); // w:t
    EndElement(XMLWriter); // w:r
    EndElement(XMLWriter); // w:p

    EndElement(XMLWriter); // w:tc
}
