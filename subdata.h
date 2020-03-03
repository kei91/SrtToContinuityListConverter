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
    quint32         m_Number;
    QTime           m_StartTime;
    CCharacterData* m_Character;
    QString         m_Line;
};

#endif // SUBDATA_H
