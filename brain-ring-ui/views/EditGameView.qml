import QtQuick 2.5
import QtQuick.Controls 1.4
import assets 1.0
import components 1.0
import BR 1.0


Item {
    property Game selectedGame
    Component.onCompleted: masterController.ui_commandController.setSelectedGame(selectedGame)

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: Style.colourBackground
    }

    ScrollView {
        id: scrollView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: commandBar.top
        anchors.margins: Style.sizeScreenMargine
        clip: true

        Column {
            spacing: Style.sizeScreenMargine
            width: scrollView.width

            Panel {
                headerText: "Детали игры"
                contentComponent:
                    Column {
                        spacing: Style.sizeControlSpacing

                        StringEditorSingleLine {
                            stringDecorator: selectedGame.ui_reference
                            anchors.left: parent.left
                            anchors.right: parent.right
                        }

                        StringEditorSingleLine {
                            stringDecorator: selectedGame.ui_name
                            anchors.left: parent.left
                            anchors.right: parent.right
                        }
                    }
            }

            InfoEditor {
                info: selectedGame.ui_supplyInfo
                headerText: "Supply Address"
            }
        }
    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_editGameViewContextCommands
    }
}
