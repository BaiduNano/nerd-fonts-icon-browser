#include "icon_container.h"
#include <QAction>
#include <QStyle>
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
    setMinimumWidth(64);

    mainLayout->setContentsMargins(1, 1, 1, 1);
    mainLayout->setSpacing(1);
    mainLayout->addWidget(iconButton);
    mainLayout->addWidget(iconLabel);

    iconButton->setText(iconStr + "");
    iconButton->setContextMenuPolicy(Qt::CustomContextMenu);
    iconButton->setStyleSheet("QPushButton { font-size: 32px; }");

    iconLabel->setText(labelStr);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setWordWrap(true);
    iconLabel->setStyleSheet("QLabel { font-size: 12px; }");

    connect(iconButton, &QPushButton::clicked, this, [&]() { copy(iconStr); });
    connect(iconButton, &QPushButton::customContextMenuRequested, this, &IconContainer::contextMenu);
}

IconContainer::~IconContainer() {
    delete mainLayout;
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

    menu.exec(globalPos + contexMenuOffset);
}

void IconContainer::copy(const QString &text) {
    emit copied(text);
}
