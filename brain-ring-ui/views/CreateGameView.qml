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
        Text {
            anchors.centerIn: parent
            text: "Create Game"
        }
    }

    CommandBar {
        commandList: masterController.ui_commandController.ui_createGameViewContextCommands
    }
}
