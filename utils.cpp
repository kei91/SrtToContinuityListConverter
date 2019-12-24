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
