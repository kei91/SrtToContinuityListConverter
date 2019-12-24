#ifndef SUBDATA_H
#define SUBDATA_H

#include <QString>
#include <QTime>

class CharacterData;

class SubData
{
public:
    SubData();

private:
    quint32        m_Number;
    QTime          m_StartTime;
    CharacterData* m_Character;
    QString        m_Line;
};

#endif // SUBDATA_H
