#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <qtimer.h>
#include "../../modules/icon_manager/icon_manager.h"

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

    QTimer *notifTimer;

    static void copyToClipboard(const QString &text);
    void spawnNotification(const QString &text);
    void onContentUpdated();
    void onNotifTimerTimeout();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif // MAINWINDOW_H
