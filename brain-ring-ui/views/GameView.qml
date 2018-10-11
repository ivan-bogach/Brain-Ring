import QtQuick 2.5
import QtQuick.Controls 1.4
import assets 1.0
import components 1.0
import BR 1.0

Item {
    Component.onCompleted: masterController.ui_commandController.ui_gameViewContextCommands[0].executed()

    property TCPClient tcpClient: masterController.ui_tcpClient
    property TCPClientsList tcpClientList: masterController.ui_tcpClientList

    property IntDecorator askQuestion: masterController.ui_settings.ui_askQuestions
    property int quantity: masterController.ui_settings.ui_quantity.ui_value

    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed

    Rectangle {
        anchors.fill: parent
        color: Style.colourTCPBar

        Text {
            id: name
            anchors.left: parent.left
            anchors.top: parent.top
            color: "white"
            text: "Задавать вопросы? " + askQuestion.ui_value
        }
        Text {
            anchors.left: name.left
            anchors.top: name.bottom
            id: ame
            text: "Количество игроков: " + quantity
            color: "white"
        }
    }

    TablePoints {
        id: table
        width: parent.width
        height: parent.height/10
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        clientList: tcpClientList
    }
}
