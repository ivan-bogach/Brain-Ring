import QtQuick 2.5
import QtQuick.Controls 1.4
import assets 1.0
import components 1.0
import BR 1.0

Item {
    Component.onCompleted: {
//        mainWindow.visibility = "FullScreen"
        masterController.ui_commandController.ui_gameViewContextCommands[0].executed()
    }
    Component.onDestruction: masterController.ui_commandController.ui_gameViewContextCommands[1].executed()

    property GamePlay gamePlay: masterController.ui_gamePlay
    property bool isAllClientsConnected: masterController.ui_gamePlay.ui_isAllPlayersConnected

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    Rectangle {
        id: mainRect
        anchors.fill: parent

        Rectangle {
            anchors.centerIn: parent
            width: parent.width

            WaitPlayers {
                gameP: gamePlay
            }
        }
    }
}
