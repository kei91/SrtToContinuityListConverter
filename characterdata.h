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
    explicit CCharacterData(QString &Name);
    explicit CCharacterData(QString &Name, Gender gender);

    void SetGender(Gender gender);

    bool operator<(const CCharacterData& compare) const;
    bool operator==(const CCharacterData& compare);
    bool operator!=(const CCharacterData& compare);
    CCharacterData& operator=(const CCharacterData& characterData);

public:
    QString m_Name;
    mutable Gender  m_Gender;
};

#endif // CHARACTERDATA_H
