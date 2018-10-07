import QtQuick 2.0
import QtQuick.Controls 2.4
import BR 1.0

Item {
    property Game game
    property bool onEdit: false

    width: parent.width
    height: onEdit ? textField.height*1.2 : text.height*1.2

    Rectangle {
        id: background
        width: parent.width
        height: parent.height

        border.color: "#f0f0f0"
        border.width: 1
        radius: 5

        Row{
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.topMargin: parent.height/20
            anchors.bottomMargin: parent.height/20

            clip: true

            Text {
                id: numQuestion
                color: "#aaaaaa"
                font.pixelSize: 20
                text: "Вопрос " + game.ui_number.ui_value
            }
            Text {
                id: text
                anchors.left: numQuestion.right
                anchors.leftMargin: 15
                width: parent.width * 0.8
                wrapMode: Text.WordWrap
                font.pixelSize: 20
                text: "   " + game.ui_text.ui_value
            }

            TextField {
                id: textField
                anchors.left: numQuestion.right
                anchors.leftMargin: 15
                width: 0
                wrapMode: TextField.WordWrap
                font.pixelSize: 20
                text: ""
                focus: true
            }

            Binding {
                target: game
                property: "ui_text"
                value: textField.text
            }
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onDoubleClicked: {
                onEdit = !onEdit
                if (onEdit){
                    text.width = 0
                    text.text = ""
                    textField.width = parent.width * 0.8
                    textField.text = "   " + game.ui_text.ui_value
                } else {
                    text.width = parent.width * 0.8
                    text.text = "   " + game.ui_text.ui_value
                    textField.width = 0
                    textField.text = ""
                }
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
                    target: numQuestion
                    color : "#409cf9"
                }
                PropertyChanges {
                    target: text
                    font.italic: true
                }
            }
        ]
    }
}

