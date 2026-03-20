#include "main_window.h"
#include "ui_main_window.h"

#include <QClipboard>
#include <QTimer>
#include "../../constants.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWindow),
    iconManager(new IconManager(this)),
    notifTimer(new QTimer(this))
{

    ui->setupUi(this);
    ui->notificationLabel->setText("");

    connect(iconManager, &IconManager::contentUpdated, this, &MainWindow::onContentUpdated);
    connect(notifTimer, &QTimer::timeout, this, &MainWindow::onNotifTimerTimeout);

    iconManager->createIconContainers(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::copyToClipboard(const QString &text) {
    qDebug().noquote() << "Copied: " << text;
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void MainWindow::spawnNotification(const QString &text) {
    ui->notificationLabel->setText("Copied to clipboard: <b>" + text + "</b>");

    notifTimer->start(Constants::notificationDuration);
}

void MainWindow::onContentUpdated() {
    quint16 index = 0;

    for (IconContainer *iconContainer : *iconManager->getIconContainers()) {
        quint16 row = index / Constants::maxColumns;
        quint16 col = index % Constants::maxColumns;

        ui->gridLayout->addWidget(iconContainer, row, col);

        connect(iconContainer, &IconContainer::copied, this, &MainWindow::copyToClipboard);
        connect(iconContainer, &IconContainer::copied, this, &MainWindow::spawnNotification);

        index++;
    }
    qDebug() << "Content updated";
}

void MainWindow::onNotifTimerTimeout() {
    ui->notificationLabel->setText("");
    notifTimer->stop();
}
