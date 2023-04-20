#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <QString>

enum class Gender
{
    female = 0,
    male
};

// represents the main character data
class CCharacterData
{
public:
    explicit CCharacterData(QString &name);
    explicit CCharacterData(QString &name, Gender gender);

    void SetGender(Gender gender);

    bool operator<(const CCharacterData& compare) const;
    bool operator==(const CCharacterData& compare);
    bool operator!=(const CCharacterData& compare);
    CCharacterData& operator=(const CCharacterData& characterData);

public:
    QString _name;
    mutable Gender  _gender;
};

#endif // CHARACTERDATA_H
