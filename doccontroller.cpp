#include "doccontroller.h"
#include "mainwindow.h"
#include "characterdata.h"
#include <QDebug>

#include <QMessageBox>

#include "pugixml/pugixml.hpp"

void CDocController::SetMainWindow(MainWindow* MainWindow)
{
    _mainWindow = MainWindow;
}

// Example of doc file
// https://sebsauvage.net/wiki/doku.php?id=word_document_generation
void CDocController::ConvertSubDataToDoc(const QString& fileName, const QString& strTitle, const std::vector<CSubData>& subData, FemaleLinesStyle style, bool useUnderline)
{
    pugi::xml_document doc;
    pugi::xml_node htmlNode = doc.append_child("html");
    htmlNode.append_attribute("xmlns:o") = "urn:schemas-microsoft-com:office:office";
    htmlNode.append_attribute("xmlns:w") = "urn:schemas-microsoft-com:office:word";
    htmlNode.append_attribute("xmlns") = "http://www.w3.org/TR/REC-html40";
    pugi::xml_node headNode = htmlNode.append_child("head");
    pugi::xml_node styleNode = headNode.append_child("style");
    styleNode.append_child(pugi::node_pcdata).set_value("body { font-family: Times New Roman;  font-size: 14pt;  line-height: 1.5; } \
                                                         table, th, td { border: 1px solid black; border-collapse: collapse; } \
                                                         th, td { border: 1px solid black; } ");

    pugi::xml_node bodyNode = htmlNode.append_child("body");
    pugi::xml_node titleNode = bodyNode.append_child("p");
    titleNode.append_attribute("align") = "right";
    pugi::xml_node boldTitleNode = titleNode.append_child("b");
    boldTitleNode.append_child(pugi::node_pcdata).set_value(strTitle.toStdString().c_str());

    pugi::xml_node tableNode = bodyNode.append_child("table");
    tableNode.append_attribute("width") = "100%";

    pugi::xml_node trTitleNode = tableNode.append_child("tr");
    std::vector<QString> titles {"Тайм-код", "Герои", "Реплики"};
    for (QString& tdTitle : titles) {
        pugi::xml_node tdTitleNode = trTitleNode.append_child("th");
        tdTitleNode.append_child(pugi::node_pcdata).set_value(tdTitle.toStdString().c_str());
    }

    for (const CSubData& data : subData) {
        pugi::xml_node trFillingNode = tableNode.append_child("tr");

        pugi::xml_node tdTimestampNode = trFillingNode.append_child("td");
        tdTimestampNode.append_attribute("valign") = "top";
        tdTimestampNode.append_child(pugi::node_pcdata).set_value(data._startTime.toString("hh:mm:ss").toStdString().c_str());

        pugi::xml_node tdNameNode = trFillingNode.append_child("td");
        tdNameNode.append_attribute("valign") = "top";
        pugi::xml_node parentNode = tdNameNode;
        if (data._character->_gender == Gender::female) {
            if (style.isBold) {
                parentNode = parentNode.append_child("b");
            }
            if (style.isUnderline) {
                parentNode = parentNode.append_child("u");
            }
            if (style.isItalic) {
                parentNode = parentNode.append_child("i");
            }
        }

        parentNode.append_child(pugi::node_pcdata).set_value(data._character->_name.toStdString().c_str());

        pugi::xml_node tdLineNode = trFillingNode.append_child("td");
        if (!useUnderline) {
            tdLineNode.append_child(pugi::node_pcdata).set_value(data._line.toStdString().c_str());
            continue;
        }


        if (data._line.size() == 0) {
            continue;
        }

        int firstUnderline = data._line[0] == '_' ? 0 : -1;
        int firstRegular = data._line[0] == '_' ? -1 : 0;
        for (int iUnderline = 1; iUnderline < data._line.size(); ++iUnderline) {
            if (data._line[iUnderline] != '_') {
                continue;
            }

            if (firstUnderline == -1) {
                firstUnderline = iUnderline + 1;
                QString temp = data._line.sliced(firstRegular, iUnderline - firstRegular);
                tdLineNode.append_child(pugi::node_pcdata).set_value(temp.toStdString().c_str());

                firstRegular = -1;
            }
            else {
                firstRegular = iUnderline + 1;
                QString temp = data._line.sliced(firstUnderline, iUnderline - firstUnderline);

                pugi::xml_node bLineNode = tdLineNode.append_child("b");
                pugi::xml_node uLineNode = bLineNode.append_child("u");
                uLineNode.append_child(pugi::node_pcdata).set_value(temp.toStdString().c_str());

                firstUnderline = -1;
            }
        }

        if (firstRegular != -1) {
            QString temp = data._line.sliced(firstRegular, data._line.size() - firstRegular);
            tdLineNode.append_child(pugi::node_pcdata).set_value(temp.toStdString().c_str());
        }
    }

    doc.save_file(fileName.toStdString().c_str(), "\t", pugi::format_raw | pugi::format_no_declaration);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Выгрузка в doc");
    msgBox.setText("Выгрузка в doc завершена");
    msgBox.exec();
}
