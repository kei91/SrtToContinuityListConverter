#include "subcontroller.h"
#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QTime>

#define START_TIME_POSITION       0
#define AMOUNT_OF_DIGITS_FOR_TIME 8

void CSubController::SetMainWindow(MainWindow* MainWindow)
{
    m_MainWindow = MainWindow;
}

const std::vector<CSubData>& CSubController::GetSubData() const
{
    return m_Sub;
}

void CSubController::ExtractDataFromFile(const QString& Filename)
{
    QRegExp reLineNumber("\\d*");
    QString prevLine("");
    QFile inputFile(Filename);

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();

          if (reLineNumber.exactMatch(line) && prevLine == "")
          {
              quint32 lineNumber = line.toUInt();
              qDebug() << "lineNumber" << lineNumber << endl;

              if (in.atEnd())
                  break;

              line = in.readLine();
              QTime startTime = QTime::fromString(line.mid(START_TIME_POSITION, AMOUNT_OF_DIGITS_FOR_TIME), "hh:mm:ss");

              qDebug() << "time" << startTime.hour() << " " << startTime.minute() << " " << startTime.second() << endl;

              while (!in.atEnd())
              {
                  line = in.readLine();

                  if (line == "")
                      break;

                  qint32 indexEndName = line.indexOf("]");
                  if (indexEndName != -1 && indexEndName + 1 < line.size())
                  {
                    QString name = line.mid(1, indexEndName - 1);
                    QString text = line.mid(indexEndName + 1, line.size()).simplified();

                    qDebug() << "name" << name << endl;
                    qDebug() << "text" << text << endl;

                    m_Sub.push_back(CSubData(lineNumber, startTime, m_MainWindow->GetCharacter(name), text));
                  }
              }
          }

          prevLine = line;
       }

       inputFile.close();
    }

    m_MainWindow->UpdateTable();
}
