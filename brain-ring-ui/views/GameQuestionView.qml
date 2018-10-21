import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property Game question
    property Settings settings: masterController.ui_settings

    anchors.fill: parent

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.colourGameViewsBackground

        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: 50
            anchors.rightMargin: 50
            color: Style.colourGameViewsBackground

            Text {
                id: questionText
                width: parent.width * 0.8
                wrapMode: Text.WordWrap
                anchors.centerIn: parent
                font.pixelSize: parent.height > 600 ? 50 : 25
                color: Style.colourGameViewsText
                text: (settings.ui_askQuestions.ui_value === 2) ? question.ui_text.ui_value : "Новый раунд"
            }
        }
    }
}

