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
void CDocController::ConvertSubDataToDoc(const QString& fileName, const QString& strTitle, const std::vector<CSubData>& subData, FemaleLinesStyle style)
{
    pugi::xml_document doc;
    pugi::xml_node htmlNode = doc.append_child("html");
    htmlNode.append_attribute("xmlns:o") = "urn:schemas-microsoft-com:office:office";
    htmlNode.append_attribute("xmlns:w") = "urn:schemas-microsoft-com:office:word";
    htmlNode.append_attribute("xmlns") = "http://www.w3.org/TR/REC-html40";
    htmlNode.append_child("head");

    pugi::xml_node bodyNode = htmlNode.append_child("body");
    pugi::xml_node  titleNode = bodyNode.append_child("h3");
    titleNode.append_child(pugi::node_pcdata).set_value(strTitle.toStdString().c_str());

    pugi::xml_node tableNode = bodyNode.append_child("table");
    tableNode.append_attribute("width") = "100%";

    pugi::xml_node trTitleNode = tableNode.append_child("tr");
    std::vector<QString> titles {"Тайм-код", "Герои", "Реплики"};
    for (QString& tdTitle : titles) {
        pugi::xml_node tdTitleNode = trTitleNode.append_child("td");
        tdTitleNode.append_child(pugi::node_pcdata).set_value(tdTitle.toStdString().c_str());
    }

    for (const CSubData& data : subData) {
        pugi::xml_node trFillingNode = tableNode.append_child("tr");

        pugi::xml_node tdTimestampNode = trFillingNode.append_child("td");
        tdTimestampNode.append_child(pugi::node_pcdata).set_value(data._startTime.toString("hh:mm:ss").toStdString().c_str());

        pugi::xml_node tdNameNode = trFillingNode.append_child("td");
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
        tdLineNode.append_child(pugi::node_pcdata).set_value(data._line.toStdString().c_str());
    }

    doc.save_file(fileName.toStdString().c_str());

    QMessageBox msgBox;
    msgBox.setWindowTitle("Выгрузка в doc");
    msgBox.setText("Выгрузка в doc завершена");
    msgBox.exec();
}
