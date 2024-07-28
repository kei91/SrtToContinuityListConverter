#include "subcontroller.h"
#include "mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QTime>
#include <QRegularExpression>
#include <QFileInfo>

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
    QFile inputFile(filename);

    if (!inputFile.open(QIODevice::ReadOnly))
    {
        _mainWindow->UpdateTable();
        return;
    }

    QFileInfo fi(filename);
    QString ext = fi.suffix();
    if (ext == "srt")
    {
        ExtractDataFromSRT(inputFile, pauseInfo);
    }
    else if (ext == "ass")
    {
        ExtractDataFromASS(inputFile, pauseInfo);
    }
    else
    {
        assert("Invalid file");
    }

    inputFile.close();
    _mainWindow->UpdateTable();
}

void CSubController::ExtractDataFromSRT(QFile& inputFile, SubPauseInfo pauseInfo)
{
    QRegularExpression reLineNumber("\\d*");
    QString prevLine("");
    QTime prevTime;
    QString lastCharacteName("");
    bool addToSameCharacter = false;
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

              qint32 indexStartName = line.indexOf("[");
              qint32 indexEndName = line.indexOf("]");
              if (indexEndName != -1 && indexEndName + 1 < line.size())
              {
                QString name = line.mid(indexStartName + 1, indexEndName - indexStartName - 1);
                QString text = line.mid(indexEndName + 1, line.size()).simplified();

                if (lastCharacteName == name)
                {
                    if (!AddToSameCharacter(pauseInfo, startTime, prevTime, text))
                    {
                        _subData.push_back(CSubData(lineNumber, startTime, _mainWindow->GetCharacter(name), text));
                    }
                }
                else
                {
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
}

/*.ass format: "Dialogue: Marked, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text"*/
void CSubController::ExtractDataFromASS(QFile& inputFile, SubPauseInfo pauseInfo)
{
    quint32 lineNumber = 1;
    QString lastCharacteName("");
    QTime prevTime;
    QRegularExpression reLineNumber("Dialogue:");
    QTextStream in(&inputFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QRegularExpressionMatch reMatch = reLineNumber.match(line);
        if (reMatch.hasMatch())
        {
           QStringList dataStr = line.split(",");
           QString startTimeString = dataStr[1];
           QString endTimeString = dataStr[2];
           QString characterName = dataStr[4];
           QString text = dataStr[9];
           for(int i = 10; i < dataStr.count(); ++i) {
               text += ", " + dataStr[i];
           }

           if (characterName == "") {
               qint32 indexStartName = line.indexOf("[");
               qint32 indexEndName = text.indexOf("]");
               if (indexEndName != -1 && indexEndName + 1 < text.size())
               {
                   characterName = text.mid(indexStartName + 1, indexEndName - indexStartName - 1);
                   text = text.mid(indexEndName + 1, text.size()).simplified();
               }
           }

           QTime startTime = QTime::fromString(startTimeString, "h:m:s.z");
           QTime endTime = QTime::fromString(endTimeString, "h:m:s.z");

           qDebug() << "time" << startTime.toString() << Qt::endl;

           if (lastCharacteName == characterName)
           {
               if (!AddToSameCharacter(pauseInfo, startTime, prevTime, text))
               {
                   _subData.push_back(CSubData(++lineNumber, startTime, _mainWindow->GetCharacter(characterName), text));
               }
           }
           else
           {
               _subData.push_back(CSubData(++lineNumber, startTime, _mainWindow->GetCharacter(characterName), text));
           }

           lastCharacteName = characterName;
           prevTime = endTime;
        }
    }
}

bool CSubController::AddToSameCharacter(SubPauseInfo pauseInfo, QTime startTime, QTime endTime, const QString& text)
{
    if (!pauseInfo.pauseEnabled)
    {
        return false;
    }

    int vecSize = _subData.size();
    if (vecSize == 0)
    {
        return false;
    }

    qint64 timeDiff = endTime.msecsTo(startTime);
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

    _subData[vecSize - 1]._line += splitStr + " " + text;

    return true;
}
