import QtQuick 2.0
import BR 1.0

Item {
    property TCPClient tcpClient
//    anchors.fill: parent
//    implicitWidth: parent.width
//    implicitHeight: text.implicitHeight
    width: text.width
    height: text.height

    Rectangle {
        width: 30
        height: 30
        color: "#ffffff"
        radius: 50
        Text {
            anchors.centerIn: parent
            color: "red"
            id: text
            text: tcpClient.ui_ip.ui_value
        }
    }

}
