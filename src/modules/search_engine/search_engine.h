#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "modules/icon_manager/icon_manager.h"

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QFutureWatcher>

class SearchEngine : public QObject {
    Q_OBJECT

private:
    QWidget *parent;
    QFutureWatcher<IconMap> *watcher;

    QPlainTextEdit *searchBar;
    IconManager *iconManager;

    IconMap allIconMap;
    IconMap displayedIconMap;

    IconMap search(const QString &querry);

    static QString processQueryString(const QString &querry);

    void dispatchSearchJob(const QString &querry);
    void textChanged();
    void searchThreadFinished();

public:
    explicit SearchEngine(QWidget *parent = nullptr);
    ~SearchEngine();

    void setSearchBar(QPlainTextEdit *searchBar);
    void setIconManager(IconManager *iconManager);

    IconMap *getDisplayedIconMap();
};

#endif // SEARCH_ENGINE_H
