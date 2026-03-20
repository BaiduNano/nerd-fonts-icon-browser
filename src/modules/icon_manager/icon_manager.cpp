#include "icon_manager.h"
#include "../../constants.h"
#include "../json_parser/json_parser.h"

#include <QFile>
#include <QMessageBox>
#include <qlogging.h>

const quint8 visibleIconLimit = 100;
const QString keyChar = "char";
const QString keyCode = "code";

IconManager::IconManager(QWidget *parent)
    : QObject(parent)
{
    auto filePath = checkPathsAndGetPath(Constants::getSearchPaths());
    if (filePath.isEmpty()) {
        QMessageBox::warning(parent, "Error", "Could not find glyphnames.json");
        return;
    }
    loadIcons(filePath);
    createIconContainers(parent);
}

IconManager::~IconManager(){
    for (IconContainer *iconContainer : iconContainers) {
        delete iconContainer;
    }
}

IconContainers *IconManager::getIconContainers() {
    return &iconContainers;
}

const QString &IconManager::checkPathsAndGetPath(const QStringList &paths) {
    for (const QString &p : paths) {
        if (QFile::exists(p))
            return p;
    }
    qDebug() << "Could not find glyphnames.json in any of the search paths";
    return QString();
}

void IconManager::loadIcons(const QString &filePath) {
    auto jsonString = JSONParser::getContents(filePath);
    auto map = JSONParser::parse(jsonString);
    quint16 iconCount = 0;

    for (const auto &[key, value] : map.asKeyValueRange()) {
        QVariantMap valMap = value.toMap();
        QString valChar = valMap[keyChar].toString();
        QString valCode = valMap[keyCode].toString();

        if (valChar.isEmpty() || valCode.isEmpty()) {
            continue;
        }
        /*
        qDebug() << "Loaded Icon";
        qDebug().noquote() << "Name: " << key;
        qDebug().noquote() << "Icon: " << valChar;
        qDebug().noquote() << "UTF-8: " << valCode;
        qDebug() << "------";
        */
        iconMap[key] = {
            {keyChar, valChar},
            {keyCode, valCode}
        };
        iconCount++;
    }
    qDebug() << "Loaded Icons: " << iconCount;
}

void IconManager::createIconContainers(QWidget *parent) {

    increment = 0;

    for (const auto &[key, value] : iconMap.asKeyValueRange()) {
        // Stack allocation doesn't work
        IconContainer *instance = new IconContainer(parent, value[keyChar], key, value[keyCode]);
        iconContainers.push_back(instance);

        if (increment >= visibleIconLimit) {
            break;
        }
        increment++;
    }
}
