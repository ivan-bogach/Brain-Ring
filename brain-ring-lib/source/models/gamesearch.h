#ifndef GAMESEARCH_H
#define GAMESEARCH_H

#include <QScopedPointer>

#include <brain-ring-lib_global.h>
#include <controllers/i-database-controller.h>
#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entity-collection.h>
#include <models/game.h>

namespace br {
namespace models {

class BRAINRINGLIBSHARED_EXPORT GameSearch : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::StringDecorator* ui_searchText READ searchText CONSTANT)
    Q_PROPERTY(QQmlListProperty<br::models::Game> ui_searchResults READ ui_searchResults NOTIFY searchResultsChanged)

public:
    GameSearch(QObject* parent = nullptr, controllers::IDatabaseController* databaseController = nullptr);
    ~GameSearch();

    data::StringDecorator* searchText();
    QQmlListProperty<Game> ui_searchResults();
    void search();
    void searchAll();

signals:
    void searchResultsChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}


#endif // GAMESEARCH_H
