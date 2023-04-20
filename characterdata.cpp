#include "characterdata.h"

CCharacterData::CCharacterData(QString &name) :
    _name(name),
    _gender(Gender::female)
{

}

CCharacterData::CCharacterData(QString &name, Gender gender) :
    _name(name),
    _gender(gender)
{

}

void CCharacterData::SetGender(Gender gender)
{
    _gender = gender;
}

bool CCharacterData::operator<(const CCharacterData& compare) const
{
    return this->_name < compare._name;
}

bool CCharacterData::operator==(const CCharacterData& compare)
{
    return (this->_name == compare._name &&
            this->_gender == compare._gender);
}

bool CCharacterData::operator!=(const CCharacterData& compare)
{
    return (this->_name != compare._name ||
            this->_gender != compare._gender);
}

CCharacterData& CCharacterData::operator=(const CCharacterData& characterData)
{
    if (this != &characterData)
    {
        this->_name = characterData._name;
        this->_gender = characterData._gender;
    }

    return *this;
}
