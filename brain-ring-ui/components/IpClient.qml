import QtQuick 2.0
import BR 1.0

Item {
    property TCPClient tcpClient

    property bool isConnected: tcpClient.ui_isConnected.ui_value

    width: text.width
    height: text.height

    Rectangle {
        width: 30
        height: 30
        color: "#ffffff"
        radius: 50
        Text {
            anchors.centerIn: parent
            color: isConnected ? "red" : "blue"
            id: text
            text: tcpClient.ui_ip.ui_value
        }
    }

}
