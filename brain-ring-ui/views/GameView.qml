import QtQuick 2.5
import QtQuick.Controls 1.4
import assets 1.0
import components 1.0
import BR 1.0

Item {
    property TCPClient tcpClient: masterController.ui_tcpClient
    property TCPClientsList tcpClientList: masterController.ui_tcpClientList

    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed

//    Rectangle {
//        anchors.fill: parent
//        color: Style.colourTCPBar
//    }

    Rectangle {
        width: parent.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: tcpBar.top

        color: Style.colourTCPBar
//        color: "red"

        ListView {
            width: parent.width
            height: parent.height
            model: tcpClientList.ui_tcpClients
            focus: true
            orientation: ListView.Horizontal
            spacing: 10

            delegate:
                IpList {
                    tcpClient: modelData
                }
        }
    }

    TCPBar {
        id: tcpBar
        commandList: masterController.ui_commandController.ui_gameViewContextCommands
    }



}
