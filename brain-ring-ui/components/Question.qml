import QtQuick 2.0
import QtQuick.Controls 1.4
import BR 1.0

Item {
    property Game game
    property StringDecorator stringDecoratorNumber
    property StringDecorator stringDecoratorText
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
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: {
                stringDecoratorNumber.ui_value = game.ui_number.ui_value
                stringDecoratorText.ui_value = text.text
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

