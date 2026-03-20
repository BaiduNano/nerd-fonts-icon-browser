#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QApplication>
#include <QStandardPaths>

namespace Constants {
    const quint8 iconFontSize = 38;
    const quint8 labelFontSize = 12;

    const quint8 maxColumns = 5;
    const quint8 maxItems = 200;
    const quint16 notificationDuration = 2000;

    const QString defaultLandingText = "Example Usages in CSS\n\n\n";
    const QString defaultLandingTextContent = "@import \"https://www.nerdfonts.com/assets/css/webfont.css\"\n\nI use <i class=\"nf nf-dev-qt\"></i>";

    inline QStringList getSearchPaths() {
        return {
            QCoreApplication::applicationDirPath() + "/glyphnames.json",
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/glyphnames.json",
            QApplication::applicationDirPath() + "/glyphnames.json"
        };
    }
}

#endif // CONSTANTS_H
