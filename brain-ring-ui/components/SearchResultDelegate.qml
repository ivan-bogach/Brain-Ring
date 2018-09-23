import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property Game game

    implicitWidth: parent.width
    implicitHeight: Math.max(gameColumn.implicitHeight, textAdress.implicitHeight) + (Style.heightDataControls/2)

    Rectangle {
        id: background
        width: parent.width
        height: parent.width
        color: Style.colourPanelBackground

        Column {
            id: gameColumn
            width: parent/2
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: Style.heightDataControls/4
            spacing: Style.heightDataControls/4

            Text {
                id: textReference
                anchors.left: parent.left
                text: game.ui_reference.ui_label + ": " + game.ui_reference.ui_value
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colourPanelFont
            }

            Text {
                id: textName
                anchors.left: parent.left
                text: game.ui_name.ui_label + ": " + game.ui_name.ui_value
                font.pixelSize: Style.pixelSizeDataControls
                color: Style.colourPanelFont
            }
        }

        Text {
            id: textAddress
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: Style.heightDataControls/4
            text: game.ui_supplyInfo.ui_fullAddress
            font.pixelSize: Style.pixelSizeDataControls
            color: Style.colourPanelFont
            horizontalAlignment: Text.AlignRight
        }

        Rectangle {
            id: borderBottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: Style.colourPanelFont
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: masterController.selectGame(game)
        }

        states: [
            State {

                name: "hover"
                PropertyChanges {
                    target: background
                    color: Style.colourPanelBackgroundHover
                }
            }

        ]
    }

}

