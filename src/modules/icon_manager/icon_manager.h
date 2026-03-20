#ifndef ICON_MANAGER_H
#define ICON_MANAGER_H

#include <QObject>
#include <QWidget>
#include "../../ui/icon_container/icon_container.h"

using IconContainers = std::vector<IconContainer*>;
using IconMap = QMap<QString, QMap<QString, QString>>;

class IconManager : public QObject {
    Q_OBJECT

private:
    IconContainers iconContainers;
    IconMap iconMap;
    quint8 increment;

    static QString checkPathsAndGetPath(const QStringList &paths);
    void loadIcons(const QString &filePath);
    void spawnCriticalError(QWidget *parent);

public:
    explicit IconManager(QWidget *parent = nullptr);
    ~IconManager() override;

    IconContainers *getIconContainers();
    IconMap getIconMap();

    void generateIconContainers(QWidget *parent, IconMap &map);
    void clearIconContainers();

signals:
    void contentUpdated();
};

#endif // ICON_MANAGER_H
