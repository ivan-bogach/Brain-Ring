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
//    Component.onDestruction: masterController.ui_commandController.ui_gameViewContextCommands[1].executed()

//from gamePlay
    property GamePlay gamePlay: masterController.ui_gamePlay
    property bool isAllClientsConnected: masterController.ui_gamePlay.ui_isAllPlayersConnected

//from Settings
    property int  numberPlayersFromSettings: masterController.ui_settings.ui_quantity.ui_value

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    Rectangle {
        id: background
        color: Style.colourGameViewsBackground
        anchors.fill: parent

        Rectangle {
            id: mainRect
            anchors.fill: parent
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            color: Style.colourGameViewsBackground

            Rectangle {
                id: listViewRect
                width: isAllClientsConnected ? 0 : parent.width*0.1*numberPlayersFromSettings
                height: isAllClientsConnected ? 0 : waitPlayers.height
                visible: isAllClientsConnected ? false : true
                anchors.centerIn: parent
                color: Style.colourGameViewsBackground

                WaitPlayers {
                    id: waitPlayers
                    gameP: gamePlay
                    numPlayersFromSettings: numberPlayersFromSettings
                }
            }

            Rectangle {
                anchors.left:  isAllClientsConnected ? parent.left : parent.right
                anchors.bottom: isAllClientsConnected ? parent.bottom : parent.top
                width: isAllClientsConnected ? parent.width : 0
                height: isAllClientsConnected ? parent.height : 0
                color: Style.colourGameViewsBackground

                Text {
                    id: readyText
                    anchors.centerIn: parent
                    visible: isAllClientsConnected ? true : false
                    font.pixelSize: 30
                    font.bold:true
                    color: Style.colourGameViewsText
                    text: qsTr("Все участники готовы!")
                }
            }
        }
    }
}
