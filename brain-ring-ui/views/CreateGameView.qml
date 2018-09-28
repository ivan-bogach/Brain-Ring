import QtQuick 2.5
import QtQuick.Controls 1.4
import BR 1.0
import assets 1.0
import components 1.0



Item {
    property Game newGame: masterController.ui_newGame
    property GameSearch gameSearch: masterController.ui_gameSearch


    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed

    AddQuestionPanel {
        stringDecoratorNumber: newGame.ui_number
        stringDecoratorText: newGame.ui_text
    }

        ListView {
            model: gameSearch.ui_searchResults

            delegate:
                QuestionsList {
                    game: modelData
                }
        }



    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_createGameViewContextCommands
    }
}
