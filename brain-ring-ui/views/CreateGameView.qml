import QtQuick 2.5
import QtQuick.Controls 1.4
import BR 1.0
import assets 1.0
import components 1.0



Item {
    property Game newGame: masterController.ui_newGame

    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed

    Rectangle {
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
                            stringDecorator: newGame.ui_reference
                            anchors.left: parent.left
                            anchors.right: parent.right
                        }

                        StringEditorSingleLine {
                            stringDecorator: newGame.ui_name
                            anchors.left: parent.left
                            anchors.right: parent.right
                        }
                }
            }

            InfoEditor {
                info: newGame.ui_supplyInfo
                headerText: "Адрес"
            }
         }
    }


    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_createGameViewContextCommands
    }
}
