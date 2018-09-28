#include "gamesearch.h"
#include<QDebug>

using namespace br::controllers;
using namespace br::data;

namespace br {
namespace models {

class GameSearch::Implementation
{
public:
    Implementation(GameSearch* _gameSearch, IDatabaseController* _databaseControler)
        : gameSearch(_gameSearch)
        , databaseControler(_databaseControler)
    {

    }

    GameSearch* gameSearch{nullptr};
    IDatabaseController* databaseControler{nullptr};
    data::StringDecorator* searchText{nullptr};
    data::EntityCollection<Game>* searchResults{nullptr};
};

GameSearch::GameSearch(QObject* parent, IDatabaseController* databaseController)
    : Entity(parent, "GameSearch")
{
    implementation.reset(new Implementation(this, databaseController));
    implementation->searchText = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "searchText", "Search Text")));
    implementation->searchResults = static_cast<EntityCollection<Game>*>(addChildCollection(new EntityCollection<Game>(this, "searchResults")));

    connect(implementation->searchResults, &EntityCollection<Game>::collectionChanged, this, &GameSearch::searchResultsChanged);
}

GameSearch::~GameSearch(){}

StringDecorator* GameSearch::searchText()
{
    return implementation->searchText;
}

QQmlListProperty<Game> GameSearch::ui_searchResults()
{
    return QQmlListProperty<Game>(this, implementation->searchResults->derivedEntities());
}

void GameSearch::search()
{
    qDebug() << "Searching for " << implementation->searchText->value() << "...";

    auto resultsArray = implementation->databaseControler->find("game", implementation->searchText->value());

    implementation->searchResults->update(resultsArray);

    qDebug() << "Found " << implementation->searchResults->baseEntities().size() << " matches";
}

void GameSearch::searchAll()
{
    qDebug() << "Searching for " << implementation->searchText->value() << "...";

    auto resultsArray = implementation->databaseControler->findAll("game");

    implementation->searchResults->update(resultsArray);

    qDebug() << "Found " << implementation->searchResults->baseEntities().size() << " matches";
}

}
}


