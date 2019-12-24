#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <QString>

enum class Gender
{
    female = 0,
    male
};

// represents the main character data
class CharacterData
{
public:
    explicit CharacterData(QString &Name);
    explicit CharacterData(QString &Name, Gender gender);

    void SetGender(Gender gender);

private:
    QString m_Name;
    Gender  m_Gender;
};

#endif // CHARACTERDATA_H
