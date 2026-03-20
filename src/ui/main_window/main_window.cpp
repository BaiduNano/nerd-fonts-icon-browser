#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainWindow),
    iconManager(new IconManager(this))
{
    ui->setupUi(this);

    for (IconContainer *iconContainer : *iconManager->getIconContainers()) {
        ui->gridLayout->addWidget(iconContainer);
        ui->gridLayout->cellRect(3, 100);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
