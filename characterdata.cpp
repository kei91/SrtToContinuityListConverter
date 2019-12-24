#include "characterdata.h"

CharacterData::CharacterData(QString &Name) :
    m_Name(Name),
    m_Gender(Gender::female)
{

}

CharacterData::CharacterData(QString &Name, Gender gender) :
    m_Name(Name),
    m_Gender(gender)
{

}

void CharacterData::SetGender(Gender gender)
{
    m_Gender = gender;
}
