#ifndef ICON_CONTAINER_H
#define ICON_CONTAINER_H

#include <QWidget>
#include <QMap>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class IconContainer : public QWidget {
    Q_OBJECT

public:
    explicit IconContainer(
        QWidget *parent = nullptr,
        const QString &iconStr = QString(),
        const QString &labelStr = QString(),
        const QString &utfStr = QString()
    );
    ~IconContainer() override;

private:
    const QPoint contexMenuOffset = QPoint(8, 16);
    QVBoxLayout *mainLayout;
    QPushButton *iconButton;
    QLabel *iconLabel;

    QString iconStr;
    QString labelStr;
    QString utfStr;

    void buttonClicked();
    void contextMenu(const QPoint &localPos);
    void copy(const QString &text);

signals:
    void copied(const QString &text);
};

#endif // ICON_CONTAINER_H
