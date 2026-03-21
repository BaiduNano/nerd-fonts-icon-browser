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
    QString processedQuery = processQueryString(text);

    dispatchSearchJob(processedQuery);
}

void SearchEngine::dispatchSearchJob(const QString &querry) {
    // querry is pass by value, pass by reference doesn't work
    QFuture<IconMap> future = QtConcurrent::run([this, querry]() {
        return this->search(querry);
    });
    watcher->setFuture(future);
}

IconMap SearchEngine::search(const QString &querry) {
    IconMap result = IconMap();

    if (querry.isEmpty()) {
        return result; }

    for (auto el = allIconMap.constBegin(); el != allIconMap.constEnd(); el++) {
        if (el.key().toLower().contains(querry)) {
            result.insert(el.key(), el.value());
        }
    }
    return result;
}

void SearchEngine::searchThreadFinished() {
    displayedIconMap = watcher->result();

    // TODO: This shi is SO not optimized
    iconManager->clearIconContainers();
    iconManager->generateIconContainers(parent, displayedIconMap);
}

QString SearchEngine::processQueryString(const QString &querry){
    QString result = querry.toLower();
    result.replace(' ', '_');
    return result;
}

IconMap *SearchEngine::getDisplayedIconMap() {
    return &displayedIconMap;
}
