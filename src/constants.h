#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QApplication>
#include <QStandardPaths>

namespace Constants {
    const quint8 iconFontSize = 38;
    const quint8 labelFontSize = 12;

    const quint8 minColumns = 5;
    const quint8 maxItems = 200;
    const quint16 notificationDuration = 2000;
    const quint16 resizeRefreshDuration = 100;
    const QVector<quint16> windowSizes = {600, 800, 1000};

    const QString defaultLandingText = "Example Usages in CSS\n\n\n";
    const QString defaultLandingTextContent = "@import \"https://www.nerdfonts.com/assets/css/webfont.css\"\n\nI use <i class=\"nf nf-dev-qt\"></i>";

    const QString fallbackFont= "/0xProtoNerdFontPropo-Regular.ttf";

    inline QStringList getSearchPaths() {
        return {
            QApplication::applicationDirPath() + "/glyphnames.json",
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/glyphnames.json",
            QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.local/share/nf-icon-browser/glyphnames.json"
        };
    }
    inline QStringList getFallbackFontPaths() {
        return {
            QApplication::applicationDirPath() + "/fallback" + fallbackFont,
            QApplication::applicationDirPath() + fallbackFont,
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/fallback" + fallbackFont,
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + fallbackFont
        };
    }
}

#endif // CONSTANTS_H
