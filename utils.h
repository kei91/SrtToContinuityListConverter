#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
    static const QString GetFileName(const QString& path);
    static const QString GetSaveFileName(const QString& path);
};

#endif // UTILS_H
