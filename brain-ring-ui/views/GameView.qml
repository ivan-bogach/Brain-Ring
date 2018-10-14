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

//from tcp
//    property TCPClient tcpClient: masterController.ui_tcpClient
//    property TCPClientsList tcpClientList: masterController.ui_tcpClientList

//from settings
//    property IntDecorator askQuestion: masterController.ui_settings.ui_askQuestions
//    property int quantity: masterController.ui_settings.ui_quantity.ui_value

//from GamePlay
    property GamePlay gamePlay: masterController.ui_gamePlay
//    property bool isAllClientsConnected: masterController.ui_gamePlay.ui_isAllClientsConnected
//    property type name: value

//internal
//    property int connectedClientsNumber: 0


    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    Rectangle {
        id: mainRect
        anchors.fill: parent

        ListView {
            anchors.fill: parent
            orientation: ListView.Horizontal
            spacing: 10

            model: gamePlay.ui_players
            delegate: Rectangle {
                width: mainRect.width/10
                Text {
                    id: topTop
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    text: modelData.ui_number.ui_value
                }
                Text {
                    id: topDown
                    anchors.top:topTop.bottom
                    anchors.topMargin: 30
                    text: modelData.ui_number.ui_label
                }

                Text {
                    id: middleTop
                    anchors.top: topDown.bottom
                    anchors.topMargin: 30
                    text: modelData.ui_points.ui_value
                }
                Text {
                    id: middleDown
                    anchors.top:middleTop.bottom
                    anchors.topMargin: 30
                    text: modelData.ui_points.ui_value
                }
                Text {
                    id: downTop
                    anchors.top: middleDown.bottom
                    anchors.topMargin: 30
                    text: modelData.ui_isConnected.ui_value
                }
                Text {
                    id: downDown
                    anchors.top:downTop.bottom
                    anchors.topMargin: 30
                    text: modelData.ui_isConnected.ui_label
                }
            }
        }
//        color: "red" : "green"

//        Text {
//            id: name
//            anchors.left: parent.left
//            anchors.top: parent.top
//            color: "white"

//            text: "Задавать вопросы? " + askQuestion.ui_value
//        }

//        Text {
//            id: ame
//            anchors.left: name.left
//            anchors.top: name.bottom
//            color: "white"

//            text: "Количество игроков: " + quantity
//        }

    }

//    TablePoints {
//        id: table
//        width: parent.width
//        height: parent.height/10
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left

//        clientList: tcpClientList
//        connectedClientsQuantity: connectedClientsNumber
//    }
}
