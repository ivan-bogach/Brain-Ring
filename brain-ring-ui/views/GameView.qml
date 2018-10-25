import QtQuick 2.5
import QtQuick.Controls 1.4
import assets 1.0
import components 1.0
import BR 1.0

Item {
//    Component.onDestruction: masterController.ui_commandController.ui_gameViewContextCommands[1].executed()

//from gamePlay
    property GamePlay gamePlay: masterController.ui_gamePlay
    property bool isAllClientsConnected: masterController.ui_gamePlay.ui_isAllPlayersConnected

//from Settings
    property int  numberPlayersFromSettings: masterController.ui_settings.ui_quantity.ui_value
    property GameSearch gameSearch: masterController.ui_gameSearch
    property string playerText

    property string bgColor: masterController.ui_settings.ui_bgColor.ui_value
    property string txtColor: masterController.ui_settings.ui_txtColor.ui_value

    Component.onCompleted: {
        mainWindow.visibility = "FullScreen"
        masterController.ui_commandController.ui_gameViewContextCommands[0].executed()

        if (numberPlayersFromSettings > 1 && numberPlayersFromSettings < 5)
        {
            playerText = "игрока"
        }
        else if(numberPlayersFromSettings == 1)
        {
            playerText = "игрок"
        }
        else
        {
            playerText = "игроков"
        }
    }

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    Rectangle {
        id: background
        color: bgColor
        anchors.fill: parent

        Rectangle {
            id: mainRect
            anchors.fill: parent
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            color: bgColor

            Text {
                id: questionsQuantity
                anchors.bottom: playersQuantity.top
                anchors.left: parent.left
                color: txtColor

                font.pixelSize: 25
                text: "Количество вопросов: " + gameSearch.ui_questionsQuantity.ui_value
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        questionsQuantity.text=""
                    }
                }
            }
            Text {
                id: playersQuantity
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                color: txtColor

                font.pixelSize: 25
                text: "Состав участников: " + numberPlayersFromSettings + " " + playerText
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        playersQuantity.text=""
                    }
                }
            }

            Rectangle {
                id: listViewRect
                width: isAllClientsConnected ? 0 : parent.width*0.1*numberPlayersFromSettings
                height: isAllClientsConnected ? 0 : waitPlayers.height
                visible: isAllClientsConnected ? false : true
                anchors.centerIn: parent
                color: bgColor

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
                color: bgColor

                Text {
                    id: readyText
                    anchors.centerIn: parent
                    visible: isAllClientsConnected ? true : false
                    font.pixelSize: 30
                    font.bold:true
                    color: txtColor
                    text: qsTr("Все участники готовы!")
                }
            }
        }
    }
}
