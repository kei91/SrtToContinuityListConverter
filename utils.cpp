#include "utils.h"
#include <QFileDialog>

const QString Utils::GetFileName(const QString& path)
{
    return QFileDialog::getOpenFileName(
                                nullptr,
                                QFileDialog::tr("Open File"),
                                path.isEmpty() ? QDir::currentPath() : path,
                                QFileDialog::tr("Subtitles (*.srt *.ass)")
                            );
}

const QString Utils::GetSaveFileName(const QString& path)
{
    return QFileDialog::getSaveFileName(
                                nullptr,
                                QFileDialog::tr("Save File"),
                                path.isEmpty() ? QDir::currentPath() : path,
                                QFileDialog::tr("Doc (*.doc)")
                            );
}
