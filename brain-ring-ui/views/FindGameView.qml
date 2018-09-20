import QtQuick 2.5
import assets 1.0
import BR 1.0
import components 1.0
import QtQml.Models 2.2

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

        ListView {
            id: itemsView
            anchors.top: searchPanel.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: Style.sizeScreenMargine
        }
        clip: true

//list of items to display
        model: gameSearch.ui_searchResults

//how to visually represent	each item
        delegate:
            Text {
            text: modelData.ui_reference.ui_label + ": " + modelData.ui_reference.ui_value
            font.pixelSize: Style.pexelSizeDataControls
            color: Style.colourPanelFont
        }

    }

    CommandBar {
        commandList: masterController.ui_commandController.ui_findGameViewContextCommands
    }
}
