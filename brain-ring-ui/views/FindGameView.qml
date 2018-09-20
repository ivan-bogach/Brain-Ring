import QtQuick 2.5
import assets 1.0
import BR 1.0
import components 1.0

Item {
    property GameSearch gameSearch: masterController.ui_gameSearch

    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed
    Rectangle {
        anchors.fill: parent
        color: Style.colourBackground

        Panel {
            id: searchPanel
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: Style.sizeScreenMargine

            headerText: "Найти игры"

            contentComponent:
                StringEditorSingleLine {
                    stringDecorator: gameSearch.ui_searchText

                    anchors.left: parent.left
                    anchors.right:  parent.right
            }
        }

    }

    CommandBar {
        commandList: masterController.ui_commandController.ui_findGameViewContextCommands
    }
}
