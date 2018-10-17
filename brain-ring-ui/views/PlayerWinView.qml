import QtQuick 2.0
import assets 1.0
import BR 1.0
import components 1.0

Item {
    property StringDecorator playerNumber
    property GamePlay gamePlayInPlayerWin: masterController.ui_gamePlay
    property int  numberPlayersFromSettings: masterController.ui_settings.ui_quantity.ui_value

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    anchors.fill: parent

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.colourTCPBar

        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: 50
            anchors.rightMargin: 50
            anchors.bottomMargin: parent.height/10
            color: Style.colourTCPBar

            Text {
                id: questionText
                anchors.centerIn: parent
                font.pixelSize: 50
                color: "#05E4B5"
                text: "Выиграл участник номер " + playerNumber.ui_value
            }
        }

        Points {
            id: points
            gamePlay: gamePlayInPlayerWin
            numPlayersFromSettings: numberPlayersFromSettings
        }
    }
}
