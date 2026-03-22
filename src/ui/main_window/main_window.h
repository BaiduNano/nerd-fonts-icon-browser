#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QTimer>

#include "modules/icon_manager/icon_manager.h"
#include "modules/search_engine/search_engine.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QWidget {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    IconManager *iconManager;
    SearchEngine *searchEngine;

    QTimer *notifTimer;
    QTimer *resizeTimer;
    QLabel *landingLabel;
    QLabel *notFoundLabel;

    quint8 calcColAmmount();

    void setupLabel();

    static void copyToClipboard(const QString &text);
    void spawnNotification(const QString &text);

    void onWindowResized();
    void onContentUpdated();
    void onNotifTimerTimeout();
    void onIconClicked(const QString &iconStr, const QString &labelStr, const QString &utfStr);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // MAINWINDOW_H
