#include "main_window.h"
#include "ui_main_window.h"

#include <QClipboard>
#include <QTimer>

#include "../../constants.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWindow),
    iconManager(new IconManager(this)),
    searchEngine(new SearchEngine(this)),
    notifTimer(new QTimer(this)),
    landingLabel(new QLabel(this))
{

    ui->setupUi(this);
    ui->notificationLabel->setText("");
    ui->iconAmmount->setText("");
    ui->gridLayout->addWidget(landingLabel);

    connect(iconManager, &IconManager::contentUpdated, this, &MainWindow::onContentUpdated);
    connect(notifTimer, &QTimer::timeout, this, &MainWindow::onNotifTimerTimeout);

    setupLandingLabel();
    searchEngine->setSearchBar(ui->searchBar);
    searchEngine->setIconManager(iconManager);

    // To initialize the label text
    onContentUpdated();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupLandingLabel() {
    landingLabel->setText(Constants::defaultLandingText + Constants::defaultLandingTextContent);
    landingLabel->setAlignment(Qt::AlignCenter);
    landingLabel->setTextFormat(Qt::PlainText);
    landingLabel->setWordWrap(true);
    landingLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
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

    ui->iconAmmount->setText("Showing " + QString::number(ammount) + " icons");

    if (ammount == 0){
        landingLabel->show();
        return;
    }

    landingLabel->hide();

    for (IconContainer *iconContainer : *iconManager->getIconContainers()) {
        quint16 row = index / Constants::maxColumns;
        quint16 col = index % Constants::maxColumns;

        ui->gridLayout->addWidget(iconContainer, row, col);

        connect(iconContainer, &IconContainer::copied, this, &MainWindow::copyToClipboard);
        connect(iconContainer, &IconContainer::copied, this, &MainWindow::spawnNotification);
        connect(iconContainer, &IconContainer::iconClicked, this, &MainWindow::onIconClicked);

        index++;
    }
    qDebug() << "Content updated";
}

void MainWindow::onNotifTimerTimeout() {
    ui->notificationLabel->setText("");
    notifTimer->stop();
}

void MainWindow::onIconClicked(const QString &iconStr, const QString &labelStr, const QString &utfStr) {
    QString passedString;

    if (ui->radioCopyIcon->isChecked()) {
        passedString = iconStr; }
    else if (ui->radioCopyName->isChecked()) {
        passedString = labelStr; }
    else if (ui->radioCopyUTF->isChecked()) {
        passedString = utfStr; }

    copyToClipboard(passedString);
    spawnNotification(passedString);
}
