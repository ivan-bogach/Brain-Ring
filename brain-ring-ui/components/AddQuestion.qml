import QtQuick 2.0
import QtQuick.Controls 1.4


Item {
    anchors.fill: parent
    anchors.horizontalCenter: parent.horizontalCenter

    Rectangle {
        width: 50
        height: 50

        border.width: 1

        TextField {
            id: numValue
            anchors.fill: parent
            font.pixelSize: 15
            horizontalAlignment: TextInput.AlignHCenter
            text: newGame.ui_number
            verticalAlignment: Qt.AlignVCenter

        }
        clip: true
    }

    Rectangle {
        width: 500
        height: 50

        border.width: 1

        TextField {
            id: textValue
            anchors.fill: parent
            horizontalAlignment: TextInput.AlignHCenter
            font.pixelSize: 15
            text: newGame.ui_text
        }
        clip: true
    }
}

