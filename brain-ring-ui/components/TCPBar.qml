import QtQuick 2.0
import assets 1.0

Item {
    property alias  commandList: commandRepeater.model

    property bool isCollapsed: false

    anchors.top: isCollapsed ? parent.bottom : parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.right: parent.right



//    height: isCollapsed ? 0 : 50

    Rectangle {
        anchors.fill: parent
        color: Style.colourTCPBar

        Row {
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
//            anchors.right: parent.right
            anchors.fill: parent

            Repeater {

                id: commandRepeater
                delegate: TCPButton {
                    onStartButtonClicked: isCollapsed = true
                    command: modelData
                }
            }
        }
    }
}

