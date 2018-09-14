import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import assets 1.0

Item {
    property alias btnText: text.text
    property color hoverColour: Style.colorNavigationButtonHover

    signal navigationButtonClicked()

//    width: Style.widthNavigationButton
    width: parent.width
    height: Style.heightNavigationButton

    Rectangle{
        id: background
        anchors.fill: parent
//        anchors.leftMargin: Style.leftMarginNavigationButton
        color: Style.colourNavigationBarBackground

        Row {
            Text {
                width: Style.leftMarginNavigationButton
            }

            Text {
                id: text
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
            states: [
                State {
                    name: "hover"
                    PropertyChanges {
                        target: background
                        color: red /*hoverColour*/
                    }
                }
            ]
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: navigationButtonClicked()
        }
    }
}


