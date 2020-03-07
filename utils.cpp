#include "utils.h"
#include <QFileDialog>

const QString Utils::GetFileName(const QString& Path)
{
    return QFileDialog::getOpenFileName(
                                nullptr,
                                QFileDialog::tr("Open File"),
                                Path.isEmpty() ? QDir::currentPath() : Path,
                                QFileDialog::tr("Subtitles (*.srt)")
                            );
}

const QString Utils::GetSaveFileName(const QString& Path)
{
    return QFileDialog::getSaveFileName(
                                nullptr,
                                QFileDialog::tr("Save File"),
                                Path.isEmpty() ? QDir::currentPath() : Path,
                                QFileDialog::tr("Doc (*.doc)")
                            );
}
