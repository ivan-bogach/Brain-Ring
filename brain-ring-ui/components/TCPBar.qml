import QtQuick 2.0
import assets 1.0

Item {
    property alias  commandList: commandRepeater.model

    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.right: parent.right

    height: Style.heightCommandBar

    Rectangle {
        anchors.fill: parent
        color: Style.colourTCPBar

        Row {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            Repeater {
                id: commandRepeater
                delegate: TCPButton {
                    command: modelData
                }
            }
        }
    }
}

