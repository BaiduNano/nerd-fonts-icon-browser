#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QApplication>
#include <QStandardPaths>

namespace Constants {
    inline QStringList getSearchPaths() {
        return {
            QCoreApplication::applicationDirPath() + "/glyphnames.json",
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/glyphnames.json",
            QApplication::applicationDirPath() + "/glyphnames.json"
        };
    }
    const quint8 maxColumns = 5;
    const quint8 maxItems = 200;
    const quint16 notificationDuration = 2000;
}

#endif // CONSTANTS_H
