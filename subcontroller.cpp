#include "subcontroller.h"
#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QTime>
#include <QRegularExpression>

#define START_TIME_POSITION       0
#define END_TIME_POSITION         17
#define AMOUNT_OF_DIGITS_FOR_TIME 12

void CSubController::SetMainWindow(MainWindow* mainWindow)
{
    _mainWindow = mainWindow;
}

const std::vector<CSubData>& CSubController::GetSubData() const
{
    return _subData;
}

void CSubController::ExtractDataFromFile(const QString& filename, SubPauseInfo pauseInfo)
{
    QRegularExpression reLineNumber("\\d*");
    QString prevLine("");
    QFile inputFile(filename);

    QTime prevTime;
    QString lastCharacteName("");
    bool addToSameCharacter = false;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QRegularExpressionMatch reMatch = reLineNumber.match(line);
          if (reMatch.hasMatch() && prevLine == "")
          {
              quint32 lineNumber = line.toUInt();
              qDebug() << "lineNumber" << lineNumber << Qt::endl;

              if (in.atEnd())
                  break;

              line = in.readLine();
              QTime startTime = QTime::fromString(line.mid(START_TIME_POSITION, AMOUNT_OF_DIGITS_FOR_TIME), "hh:mm:ss,zzz");
              QTime endTime = QTime::fromString(line.mid(END_TIME_POSITION, AMOUNT_OF_DIGITS_FOR_TIME), "hh:mm:ss,zzz");

              qDebug() << "time" << startTime.toString() << Qt::endl;
              qDebug() << "prevTime" << prevTime.toString() << Qt::endl;

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

                    qDebug() << "name" << name << Qt::endl;
                    qDebug() << "text" << text << Qt::endl;

                    addToSameCharacter = false;
                    if (pauseInfo.pauseEnabled && lastCharacteName == name) {
                        int vecSize = _subData.size();
                        if (vecSize > 0) {
                            qint64 timeDiff = prevTime.msecsTo(startTime);
                            QString splitStr("");
                            if (timeDiff >= pauseInfo.smallPauseStart && timeDiff <= pauseInfo.smallPauseEnd) {
                                splitStr = " /";
                            }
                            else if (timeDiff > pauseInfo.smallPauseEnd && timeDiff <= pauseInfo.bigPauseStart) {
                                splitStr = " // ";
                            }
                            else if (timeDiff > pauseInfo.bigPauseStart) {
                                splitStr = " // " + (startTime.hour() == 0 ? startTime.toString("mm:ss") : startTime.toString("hh:mm:ss")) + " ";
                            }

                            addToSameCharacter = true;
                            _subData[vecSize - 1]._line += splitStr + " " + text;
                        }
                    }

                    if (!addToSameCharacter) {
                        _subData.push_back(CSubData(lineNumber, startTime, _mainWindow->GetCharacter(name), text));
                    }

                    lastCharacteName = name;
                    prevTime = endTime;
                  }
                  else if (_subData.size() > 0){
                      _subData[_subData.size() - 1]._line += " " + line;
                  }

              }
          }

          prevLine = line;
       }

       inputFile.close();
    }

    _mainWindow->UpdateTable();
}
