import QtQuick 2.0
import assets 1.0
import BR 1.0
import components 1.0

Item {
    property StringDecorator playerNumber
    property GamePlay gamePlayInPlayerWin: masterController.ui_gamePlay
    property int  numberPlayersFromSettings: masterController.ui_settings.ui_quantity.ui_value

    property string bgColor: masterController.ui_settings.ui_bgColor.ui_value
    property string txtColor: masterController.ui_settings.ui_txtColor.ui_value


//internal
    property bool isFullSize: true

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
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

    anchors.fill: parent

    Rectangle {
        id: background
        anchors.fill: parent
        color: bgColor

        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: 50
            anchors.rightMargin: 50
            anchors.bottomMargin: parent.height/10
            color: bgColor

            Text {
                id: questionText
                anchors.centerIn: parent
                font.pixelSize: 50
                color: txtColor
                text: "Выиграл участник номер " + playerNumber.ui_value
            }
        }

        Points {
            id: points
            gamePlay: gamePlayInPlayerWin
            numPlayersFromSettings: numberPlayersFromSettings
            winnerNumber: playerNumber
        }
    }
}
