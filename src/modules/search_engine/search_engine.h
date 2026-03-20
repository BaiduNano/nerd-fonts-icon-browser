#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "../icon_manager/icon_manager.h"

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
    IconMap search(const QString &querry);

public:
    explicit SearchEngine(QWidget *parent = nullptr);
    ~SearchEngine();

    void setSearchBar(QPlainTextEdit *searchBar);
    void setIconManager(IconManager *iconManager);
    void textChanged();

    void searchThreadFinished();
};

#endif // SEARCH_ENGINE_H
