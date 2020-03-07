#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
    static const QString GetFileName(const QString& Path);
    static const QString GetSaveFileName(const QString& Path);
};

#endif // UTILS_H
