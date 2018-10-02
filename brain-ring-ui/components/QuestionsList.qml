import QtQuick 2.0
import BR 1.0

Item {
    property Game game
//    anchors.fill: parent
//    implicitWidth: parent.width
//    implicitHeight: text.implicitHeight
    width: parent.width
    height: text.height

    Rectangle {
        width: parent.width
        height: parent.height

        border.color: "#f0f0f0"
        border.width: 1
        radius: 5

        Row{
            anchors.fill: parent
            anchors.leftMargin: parent.width/20
            anchors.topMargin: parent.height/20
            anchors.bottomMargin: parent.height/20

            Text {
                id: textQuestion
                color: "#aaaaaa"
                font.pixelSize: 20
                text: "Вопрос №" + game.ui_number.ui_value
            }
            Text {
                id: text
                wrapMode: wrap
                font.pixelSize: 20
                text: "   " + game.ui_text.ui_value + "."
            }
        }

    }


}

