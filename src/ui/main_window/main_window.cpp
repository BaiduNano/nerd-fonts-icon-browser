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
    ui->iconAmmount->setText("");

    connect(iconManager, &IconManager::contentUpdated, this, &MainWindow::onContentUpdated);
    connect(notifTimer, &QTimer::timeout, this, &MainWindow::onNotifTimerTimeout);

    iconManager->createIconContainers(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::copyToClipboard(const QString &text) {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);

    qDebug().noquote() << "Copied: " << text;
}

void MainWindow::spawnNotification(const QString &text) {
    ui->notificationLabel->setText("Copied to clipboard: <b>" + text + "</b>");

    notifTimer->stop();
    notifTimer->start(Constants::notificationDuration);
}

void MainWindow::onContentUpdated() {
    quint16 index = 0;
    quint16 ammount = iconManager->getIconContainers()->size();

    for (IconContainer *iconContainer : *iconManager->getIconContainers()) {
        quint16 row = index / Constants::maxColumns;
        quint16 col = index % Constants::maxColumns;

        ui->gridLayout->addWidget(iconContainer, row, col);

        connect(iconContainer, &IconContainer::copied, this, &MainWindow::copyToClipboard);
        connect(iconContainer, &IconContainer::copied, this, &MainWindow::spawnNotification);
        connect(iconContainer, &IconContainer::iconClicked, this, &MainWindow::onIconClicked);

        index++;
    }

    ui->iconAmmount->setText("Showing " + QString::number(ammount) + " icons");

    qDebug() << "Content updated";
}

void MainWindow::onNotifTimerTimeout() {
    ui->notificationLabel->setText("");
    notifTimer->stop();
}

void MainWindow::onIconClicked(const QString &iconStr, const QString &labelStr, const QString &utfStr) {
    if (ui->radioCopyIcon->isChecked()) {
        copyToClipboard(iconStr);
        spawnNotification(iconStr);
    } else if (ui->radioCopyName->isChecked()) {
        copyToClipboard(labelStr);
        spawnNotification(labelStr);
    } else if (ui->radioCopyUTF->isChecked()) {
        copyToClipboard(utfStr);
        spawnNotification(utfStr);
    }
}
