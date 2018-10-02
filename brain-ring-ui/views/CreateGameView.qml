import QtQuick 2.5
import QtQuick.Controls 1.4
import BR 1.0
import assets 1.0
import components 1.0



Item {
    property Game newGame: masterController.ui_newGame
    property GameSearch gameSearch: masterController.ui_gameSearch

    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right

    anchors.leftMargin: 15
    anchors.rightMargin: 15

    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed

    Rectangle {
        id: addQuestionRect
        width: parent.width
        height: addQuestionPanel.height + 100



        AddQuestionPanel {
            id: addQuestionPanel
            stringDecoratorNumber: newGame.ui_number
            stringDecoratorText: newGame.ui_text
        }
    }

    Rectangle {

        width: parent.width
        anchors.top: addQuestionRect.bottom
        anchors.bottom: commandBar.top

        ScrollView {
            width: parent.width
            height: parent.height


            ListView {
                spacing: 5
                model: gameSearch.ui_searchResults

                delegate:
                    QuestionsList {
                        game: modelData
                    }
            }
        }

    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_createGameViewContextCommands
    }
}
