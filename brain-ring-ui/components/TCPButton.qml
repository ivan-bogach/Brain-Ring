import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import assets 1.0

Item {
    property alias startBtnText: startText.text
    property alias stopBtnText: stopText.text

    property color hoverColour: Style.colorNavigationButtonHover

    signal tcpButtonClicked()

//    width: Style.widthNavigationButton
    width: parent.width
    height: Style.heightNavigationButton

    Rectangle{
        id: background
        anchors.fill: parent
        color: Style.colourNavigationBarBackground

        Row {
            Text {
                id: startText
                width: Style.widthNavigationButton
                height: Style.heightNavigationButton
                font {
                    pixelSize: Style.pixelSizeNavigationBarFont
                    family: "Courier New"
                    bold: true
                }
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                color: Style.colourNavigationBarFont
                text: "SET ME!!!"

            }

            Text {
                id: stopText
                width: Style.widthNavigationButton
                height: Style.heightNavigationButton
                font {
                    pixelSize: Style.pixelSizeNavigationBarFont
                    family: "Courier New"
                    bold: true
                }
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                color: Style.colourNavigationBarFont
                text: "SET ME!!!"

            }
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: tcpButtonClicked()
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: hoverColour
                }
            }
        ]
    }
}


