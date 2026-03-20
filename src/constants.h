#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QApplication>
#include <QStandardPaths>

namespace Constants {
    const quint8 maxColumns = 5;
    const quint8 maxItems = 200;
    const quint16 notificationDuration = 2000;

    inline QStringList getSearchPaths() {
        return {
            QCoreApplication::applicationDirPath() + "/glyphnames.json",
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/glyphnames.json",
            QApplication::applicationDirPath() + "/glyphnames.json"
        };
    }
}

#endif // CONSTANTS_H
