import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property Game question
    property Settings settings: masterController.ui_settings

    anchors.fill: parent

    property string bgColor: masterController.ui_settings.ui_bgColor.ui_value
    property string txtColor: masterController.ui_settings.ui_txtColor.ui_value

//internal
    property bool isFullSize: true

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
                console.log("1111111111111111111")
            } else {
                mainWindow.visibility = "Windowed"
                console.log("33333333333333333333")
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
                width: parent.width * 0.8
                wrapMode: Text.WordWrap
                anchors.centerIn: parent
                font.pixelSize: parent.height > 600 ? 50 : 25
                color: txtColor
                text: (settings.ui_askQuestions.ui_value === 2) ? question.ui_text.ui_value : "Новый раунд"
            }
        }
    }
}

