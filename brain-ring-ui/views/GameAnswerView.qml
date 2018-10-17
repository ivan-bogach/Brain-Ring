import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property StringDecorator playerNumber

    anchors.fill: parent

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.colourTCPBar

        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: 50
            anchors.rightMargin: 50
            color: Style.colourTCPBar

            Text {
                id: questionText
                anchors.centerIn: parent
                font.pixelSize: 50
                color: "#05E4B5"
                text: "Отвечает участник номмер " + playerNumber.ui_value
            }
        }
    }

}
