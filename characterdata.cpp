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

bool CharacterData::operator<(const CharacterData& compare) const
{
    return this->m_Name < compare.m_Name;
}

bool CharacterData::operator==(const CharacterData& compare)
{
    return (this->m_Name == compare.m_Name &&
            this->m_Gender == compare.m_Gender);
}

bool CharacterData::operator!=(const CharacterData& compare)
{
    return (this->m_Name != compare.m_Name ||
            this->m_Gender != compare.m_Gender);
}

CharacterData& CharacterData::operator=(const CharacterData& characterData)
{
    if (this != &characterData)
    {
        this->m_Name = characterData.m_Name;
        this->m_Gender = characterData.m_Gender;
    }

    return *this;
}
