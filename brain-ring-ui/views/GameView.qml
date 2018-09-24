import QtQuick 2.5
import assets 1.0
import components 1.0


Item {

    Rectangle {
        anchors.fill: parent
        Text {
            anchors.centerIn: parent
            text: "GAME!!!"
        }

        TCPBar {
            id: tcpBar
            anchors.fill: parent
            commandList: masterController.ui_commandController.ui_gameViewContextCommands
        }

    }

}
