#include "subcontroller.h"
#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

void SubController::SetMainWindow(MainWindow* MainWindow)
{
    m_MainWindow = MainWindow;
}

void SubController::ExtractDataFromFile(const QString& Filename)
{
    QRegExp re("\\d*");
    QString PrevLine("");
    QFile inputFile(Filename);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          qDebug() << "line" << line << endl;

          if (re.exactMatch(line) && PrevLine == "")
             qDebug() << "new sub" << endl;

          PrevLine = line;
       }
       inputFile.close();
    }
}
