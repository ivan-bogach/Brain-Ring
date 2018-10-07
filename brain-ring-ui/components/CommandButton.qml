import QtQuick 2.0
import BR 1.0
import assets 1.0

Item {
    property Command command

    width:  50
    height: 50


    Rectangle {
        id: background
        anchors.fill: parent

        Text {
            id: textIcon
            anchors.centerIn: parent

            font {
                family: Style.fontAwesome
                pixelSize: 50
            }
            color: command.ui_canExecute ? "#aaaaaa" : Style.colourCommandBarFontDisabled
            text: command.ui_iconCharacter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: if(command.ui_canExecute) {
                           command.executed();
                       }
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: "#ebf5fe"
                }
                PropertyChanges {
                    target: textIcon
                    color : "#409cf9"
                }

            }

        ]

    }
}

