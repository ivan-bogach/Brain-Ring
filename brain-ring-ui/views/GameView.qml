import QtQuick 2.5
import assets 1.0
import components 1.0
import BR 1.0

Item {
    property TCPClient tcpClient: masterController.ui_tcpClient
    property TCPClientsList tcpClientList: masterController.ui_tcpClientList
    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed

    Rectangle {
        anchors.fill: parent

//        color: "red"

        ListView {
            model: tcpClientList.ui_tcpClients

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
