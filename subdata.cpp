#include "subdata.h"
#include "characterdata.h"

SubData::SubData(quint32 number, QTime startTime, CharacterData* character, QString line) :
    m_Number(number),
    m_StartTime(startTime),
    m_Character(character),
    m_Line(line)
{

}
