import QtQuick 2.0
import BR 1.0

Item {
    property Game game
//    anchors.fill: parent
//    implicitWidth: parent.width
//    implicitHeight: text.implicitHeight
    width: parent.width
    height: text.height

    Text {
        id: text
        text: "Вопрос №" + game.ui_number.ui_value + "   " + game.ui_text.ui_value + "."
    }
}

