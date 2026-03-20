#include "icon_manager.h"
#include "../../constants.h"
#include "../json_parser/json_parser.h"

#include <QFile>
#include <QMessageBox>

const QString keyChar = "char";
const QString keyCode = "code";

IconManager::IconManager(QWidget *parent)
    : QObject(parent)
{
    auto filePath = checkPathsAndGetPath(Constants::getSearchPaths());
    if (filePath.isEmpty()) {
        spawnCriticalError(parent);
        return;
    }
    loadIcons(filePath);
}

IconManager::~IconManager(){
    for (IconContainer *iconContainer : iconContainers) {
        delete iconContainer;
    }
}

IconContainers *IconManager::getIconContainers() {
    return &iconContainers;
}

QString IconManager::checkPathsAndGetPath(const QStringList &paths) {
    for (const QString &p : paths) {
        if (QFile::exists(p))
            return p;
    }
    qDebug() << "glyphnames.json not found";
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

    increment = 1;

    for (const auto &[key, value] : iconMap.asKeyValueRange()) {
        // Stack allocation doesn't work
        IconContainer *instance = new IconContainer(parent, value[keyChar], key, value[keyCode]);
        iconContainers.push_back(instance);

        if (increment >= Constants::maxItems) {
            break;
        }
        increment++;
    }
    emit contentUpdated();
}

void IconManager::spawnCriticalError(QWidget *parent) {
    QMessageBox msgBox(parent);

    QString url = "https://github.com/ryanoasis/nerd-fonts/blob/master/glyphnames.json";

    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Error");
    msgBox.setText("<b>Cannot find glyphnames.json</b>");
    msgBox.setInformativeText(
        "Please download the file below and place it in the application folder:"
        "<br><br>"
        "<a href='" + url + "'>" + url + "</a>"
    );
    msgBox.setTextInteractionFlags(Qt::LinksAccessibleByMouse | Qt::TextSelectableByMouse);

    msgBox.exec();
}

void IconManager::clearIconContainers() {
    for (IconContainer *container : iconContainers) {
        delete container;
    }
    iconContainers.clear();
    emit contentUpdated();
}
