import QtQuick 2.0
import BR 1.0
import assets 1.0

Item {
    property Command command

    property bool isStarted: false

    property bool isCollapsed: false

    anchors.fill: parent


    signal startButtonClicked()

    Rectangle {
        id: background
        width:  isCollapsed ? 0 : Style.widthTCPButton
        height: Style.widthTCPButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        radius: 50


//        Text {
//            id: textIcon
//            anchors.centerIn: parent
//            anchors.verticalCenterOffset: -10
//            font {
//                family: Style.fontAwesome
//                pixelSize: Style.pixelSizeCommandBarIcon
//            }
//            color: command.ui_canExecute ? Style.colourCommandBarFont : Style.colourCommandBarFontDisabled
//            text: command.ui_iconCharacter
//            horizontalAlignment: Text.AlignHCenter
//        }

        Text {
            id: textDescription
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
//            font.pixelSize: Style.pixelSizeCommandBarText
            font.pixelSize: 10
            color: command.ui_canExecute ? Style.colourCommandBarFont : Style.colourCommandBarFontDisabled
            text: command.ui_description
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: if(command.ui_canExecute) {
                           command.executed();
                           startButtonClicked();
                           isCollapsed = true;
                       }
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: Qt.darker(Style.colourCommandBarBackground)
                }
            }

        ]

    }
}

