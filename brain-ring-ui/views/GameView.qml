import QtQuick 2.5
import QtQuick.Controls 1.4
import assets 1.0
import components 1.0
import BR 1.0

Item {
    property TCPClient tcpClient: masterController.ui_tcpClient
    property TCPClientsList tcpClientList: masterController.ui_tcpClientList

    Component.onCompleted: masterController.ui_commandController.ui_gameViewContextCommands[0].executed()

    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed

    Rectangle {
        anchors.fill: parent
        color: Style.colourTCPBar
    }


    Rectangle {
        width: 500
        height: 50

        anchors.bottom: parent.bottom

        color: "red"
        anchors.horizontalCenter: parent.horizontalCenter

        ListView {
            width: parent.width
            height: parent.height
            model: tcpClientList.ui_tcpClients
            focus: true
            orientation: ListView.Horizontal
            spacing: 10

            delegate:
                IpClient {
                    tcpClient: modelData
                }
        }
    }



}
