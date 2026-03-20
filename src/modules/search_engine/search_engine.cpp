#include "search_engine.h"

#include <QtConcurrent/QtConcurrent>

SearchEngine::SearchEngine(QWidget *parent):
    QObject(parent),
    parent(parent),
    watcher(new QFutureWatcher<IconMap>(this))
{
    connect(watcher, &QFutureWatcher<IconMap>::finished, this, &SearchEngine::searchThreadFinished);
}

SearchEngine::~SearchEngine() = default;

void SearchEngine::setSearchBar(QPlainTextEdit *searchBar) {
    this->searchBar = searchBar;
    connect(this->searchBar, &QPlainTextEdit::textChanged, this, &SearchEngine::textChanged);
}

void SearchEngine::setIconManager(IconManager *iconManager) {
    this->iconManager = iconManager;
    allIconMap = iconManager->getIconMap();
}

void SearchEngine::textChanged() {
    QString text = searchBar->toPlainText();
    QFuture<IconMap> future = QtConcurrent::run([this, text]() {
        return this->search(text);
    });
    watcher->setFuture(future);
}

IconMap SearchEngine::search(const QString &querry) {
    IconMap result = IconMap();

    if (querry.isEmpty()) {
        return result; }

    QString lowerQuerry = querry.toLower();

    for (auto it = allIconMap.constBegin(); it != allIconMap.constEnd(); ++it) {
        if (it.key().toLower().contains(lowerQuerry)) {
            result.insert(it.key(), it.value());
        }
    }
    return result;
}

void SearchEngine::searchThreadFinished() {
    IconMap result = watcher->result();

    // TODO: This shi is so not optimized
    iconManager->clearIconContainers();
    iconManager->generateIconContainers(parent, result);
}
