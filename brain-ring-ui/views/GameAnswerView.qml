import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property StringDecorator playerNumber

    property string bgColor: masterController.ui_settings.ui_bgColor.ui_value
    property string txtColor: masterController.ui_settings.ui_txtColor.ui_value

//internal
    property bool isFullSize: true

    anchors.fill: parent

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/EmptyQuestionsListView.qml")
    }

    MouseArea {
        anchors.fill: parent
        onDoubleClicked: {
            isFullSize = !isFullSize
            if (isFullSize){
                mainWindow.visibility = "FullScreen"
            } else {
                mainWindow.visibility = "Windowed"
            }
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: bgColor

        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: 50
            anchors.rightMargin: 50
            color: bgColor

            Text {
                id: questionText
                anchors.centerIn: parent
                font.pixelSize: 50
                color: txtColor
                text: "Отвечает участник номер " + playerNumber.ui_value
            }
        }
    }
}
