import QtQuick 2.0
import BR 1.0

Item {
    property TCPClient tcpClient
//    anchors.fill: parent
//    implicitWidth: parent.width
//    implicitHeight: text.implicitHeight
    width: parent.width
    height: text.height

    Text {
        color: "red"
        id: text
        text: " ip:" + tcpClient.ui_ip.ui_value + "."
    }
}
