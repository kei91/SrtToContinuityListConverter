#include "subdata.h"
#include "characterdata.h"

CSubData::CSubData(quint32 number, QTime startTime, CCharacterData* character, QString line) :
    _number(number),
    _startTime(startTime),
    _character(character),
    _line(line)
{

}
