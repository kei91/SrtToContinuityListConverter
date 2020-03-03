#include "subdata.h"
#include "characterdata.h"

CSubData::CSubData(quint32 number, QTime startTime, CCharacterData* character, QString line) :
    m_Number(number),
    m_StartTime(startTime),
    m_Character(character),
    m_Line(line)
{

}
