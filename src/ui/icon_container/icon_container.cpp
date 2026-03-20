#include "icon_container.h"
#include <QAction>
#include <QMenu>

IconContainer::IconContainer(QWidget *parent, const QString &iconStr, const QString &labelStr, const QString &utfStr):
    QWidget(parent),
    iconStr(iconStr),
    labelStr(labelStr),
    utfStr(utfStr),

    mainLayout(new QVBoxLayout(parent)),
    iconLabel(new QLabel(parent)),
    iconButton(new QPushButton(parent))
{

    setLayout(mainLayout);

    mainLayout->addWidget(iconButton);
    mainLayout->addWidget(iconLabel);

    iconButton->setText(iconStr);
    iconButton->setContextMenuPolicy(Qt::CustomContextMenu);
    iconLabel->setText(labelStr);
    iconLabel->setAlignment(Qt::AlignCenter);

    connect(iconButton, &QPushButton::clicked, this, &IconContainer::buttonClicked);
    connect(iconButton, &QPushButton::customContextMenuRequested, this, &IconContainer::contextMenu);
}

IconContainer::~IconContainer() {
    delete mainLayout;
}

void IconContainer::buttonClicked() {
   copy(iconStr);
}

void IconContainer::contextMenu(const QPoint &localPos) {
    QMenu menu(this);

    QAction *copyIcon = menu.addAction("Copy Icon");
    QAction *copyName = menu.addAction("Copy Name");
    QAction *copyUtf = menu.addAction("Copy UTF");

    connect(copyIcon, &QAction::triggered, this, [&]() { copy(iconStr); });
    connect(copyName, &QAction::triggered, this, [&]() { copy(labelStr); });
    connect(copyUtf, &QAction::triggered, this, [&]() { copy(utfStr); });

    QPoint globalPos = mapToGlobal(localPos);
    QPoint offset = QPoint(16, 8);

    menu.exec(globalPos + offset);
}

void IconContainer::copy(const QString &text) {
    qDebug().noquote() << "Copied: " << text;
    emit copied(text);
}
