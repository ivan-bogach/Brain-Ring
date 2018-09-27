import QtQuick 2.5
import QtQuick.Controls 1.4
import BR 1.0
import assets 1.0
import components 1.0

Item {
    property Game newGame: masterController.ui_newGame

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
        anchors.margins: Style.sizeScreenMargin

        clip: true

        Column {
            spacing: Style.sizeScreenMargin
            width: scrollView.width

            StringEditorSingleLine {
                stringDecorator: newGame.ui_name
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }
    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_createGameViewContextCommands
    }
}

