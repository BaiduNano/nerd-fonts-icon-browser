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
    quint8 increment = 0;

    const QString &checkPathsAndGetPath(const QStringList &paths);
    void loadIcons(const QString &filePath);
    void createIconContainers(QWidget *parent);

public:
    explicit IconManager(QWidget *parent = nullptr);
    ~IconManager() override;

    IconContainers *getIconContainers();
};

#endif // ICON_MANAGER_H
