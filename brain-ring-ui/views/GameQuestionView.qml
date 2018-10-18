import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property Game question

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
                anchors.centerIn: parent
                font.pixelSize: 50
                color: Style.colourGameViewsText
                text: question.ui_text.ui_value
            }
        }
    }

}

