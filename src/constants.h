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
}

#endif // CONSTANTS_H
