#include "utils.h"
#include <QFileDialog>

const QString Utils::GetFileName()
{
    return QFileDialog::getOpenFileName(
                                nullptr,
                                QFileDialog::tr("Open File"),
                                QDir::currentPath(),
                                QFileDialog::tr("Subtitles (*.srt)")
                            );
}

const QString Utils::GetSaveFileName()
{
    return QFileDialog::getSaveFileName(
                                nullptr,
                                QFileDialog::tr("Save File"),
                                QDir::currentPath(),
                                QFileDialog::tr("Doc (*.doc)")
                            );
}
