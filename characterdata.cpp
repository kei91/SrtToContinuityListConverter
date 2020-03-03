#include "characterdata.h"

CCharacterData::CCharacterData(QString &Name) :
    m_Name(Name),
    m_Gender(Gender::female)
{

}

CCharacterData::CCharacterData(QString &Name, Gender gender) :
    m_Name(Name),
    m_Gender(gender)
{

}

void CCharacterData::SetGender(Gender gender)
{
    m_Gender = gender;
}

bool CCharacterData::operator<(const CCharacterData& compare) const
{
    return this->m_Name < compare.m_Name;
}

bool CCharacterData::operator==(const CCharacterData& compare)
{
    return (this->m_Name == compare.m_Name &&
            this->m_Gender == compare.m_Gender);
}

bool CCharacterData::operator!=(const CCharacterData& compare)
{
    return (this->m_Name != compare.m_Name ||
            this->m_Gender != compare.m_Gender);
}

CCharacterData& CCharacterData::operator=(const CCharacterData& characterData)
{
    if (this != &characterData)
    {
        this->m_Name = characterData.m_Name;
        this->m_Gender = characterData.m_Gender;
    }

    return *this;
}
