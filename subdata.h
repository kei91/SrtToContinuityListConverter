#ifndef SUBDATA_H
#define SUBDATA_H

#include <QString>
#include <QTime>

class CCharacterData;

class CSubData
{
public:
    CSubData(quint32 number, QTime startTime, CCharacterData* character, QString line);

public:
    quint32         _number;
    QTime           _startTime;
    CCharacterData* _character;
    QString         _line;
};

#endif // SUBDATA_H
