#ifndef ICON_CONTAINER_H
#define ICON_CONTAINER_H

#include <QWidget>
#include <QMap>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>

class IconContainer : public QWidget {
    Q_OBJECT

public:
    inline static QFont *fallbackFont = nullptr;

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
    void iconClicked(const QString &icon, const QString &label, const QString &utf);
};

#endif // ICON_CONTAINER_H
