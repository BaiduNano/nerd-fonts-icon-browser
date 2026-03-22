#include "main_window.h"
#include "ui_main_window.h"

#include <QClipboard>
#include <QTimer>

#include "constants.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWindow),
    iconManager(new IconManager(this)),
    searchEngine(new SearchEngine(this)),
    notifTimer(new QTimer(this)),
    resizeTimer(new QTimer(this)),
    landingLabel(new QLabel(this)),
    notFoundLabel(new QLabel(this))
{

    ui->setupUi(this);
    ui->notificationLabel->setText("");
    ui->iconAmmount->setText("");
    ui->gridLayout->addWidget(landingLabel);
    ui->gridLayout->addWidget(notFoundLabel);
    if (IconContainer::fallbackFont != nullptr){
        ui->notificationLabel->setFont(*IconContainer::fallbackFont);
    }

    resizeTimer->setSingleShot(true);

    connect(iconManager, &IconManager::contentUpdated, this, &MainWindow::onContentUpdated);
    connect(notifTimer, &QTimer::timeout, this, &MainWindow::onNotifTimerTimeout);
    connect(resizeTimer, &QTimer::timeout, this, &MainWindow::onWindowResized);

    setupLabel();

    searchEngine->setSearchBar(ui->searchBar);
    searchEngine->setIconManager(iconManager);

    // To initialize the label text
    onContentUpdated();
}

MainWindow::~MainWindow() {
    delete ui;
}

quint8 MainWindow::calcColAmmount() {
    quint16 width = this->width();
    quint8 base = Constants::minColumns;

    for (auto i = 0; i < Constants::windowSizes.length(); i++) {
        if (width < Constants::windowSizes[i]) {
            return base + i; }
    }
    return base + Constants::windowSizes.length();
}

void MainWindow::setupLabel() {
    landingLabel->setText(Constants::defaultLandingText + Constants::defaultLandingTextContent);
    landingLabel->setAlignment(Qt::AlignCenter);
    landingLabel->setTextFormat(Qt::PlainText);
    landingLabel->setWordWrap(true);
    landingLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    notFoundLabel->setText("Not found.");
    notFoundLabel->setAlignment(Qt::AlignCenter);
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
    quint8 colAmmount = calcColAmmount();

    ui->iconAmmount->setText("Showing " + QString::number(ammount) + " icons");

    if (ui->searchBar->toPlainText().isEmpty()){
        landingLabel->show();
        notFoundLabel->hide();
        return;
    }
    if (ammount == 0) {
        notFoundLabel->show();
        landingLabel->hide();
        return;
    }

    landingLabel->hide();
    notFoundLabel->hide();

    for (IconContainer *iconContainer : *iconManager->getIconContainers()) {
        quint16 row = index / colAmmount;
        quint16 col = index % colAmmount;

        ui->gridLayout->addWidget(iconContainer, row, col);

        connect(iconContainer, &IconContainer::copied, this, &MainWindow::copyToClipboard);
        connect(iconContainer, &IconContainer::copied, this, &MainWindow::spawnNotification);
        connect(iconContainer, &IconContainer::iconClicked, this, &MainWindow::onIconClicked);

        index++;
    }
    qDebug() << "Content updated, found " << ammount << " icons";
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

void MainWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    resizeTimer->stop();
    resizeTimer->start(Constants::resizeRefreshDuration);
}

void MainWindow::onWindowResized() {
    // TODO: heavy af, better way to do this
    IconMap temp(*searchEngine->getDisplayedIconMap());
    iconManager->clearIconContainers();
    iconManager->generateIconContainers(this, temp);
}
