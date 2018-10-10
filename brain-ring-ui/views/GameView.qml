import QtQuick 2.5
import QtQuick.Controls 1.4
import assets 1.0
import components 1.0
import BR 1.0

Item {
    Component.onCompleted: masterController.ui_commandController.ui_gameViewContextCommands[0].executed()

    property TCPClient tcpClient: masterController.ui_tcpClient
    property TCPClientsList tcpClientList: masterController.ui_tcpClientList

    property IntDecorator askQuestion: masterController.ui_settings.ui_askQuestions
    property int quantity: masterController.ui_settings.ui_quantity.ui_value


    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed

    Rectangle {
        anchors.fill: parent
        color: Style.colourTCPBar

        Text {
            id: name
            anchors.left: parent.left
            anchors.top: parent.top
            color: "white"
            text: "Задавать вопросы? " + askQuestion.ui_value
        }
        Text {
            anchors.left: name.left
            anchors.top: name.bottom
            id: ame
            text: "Количество игроков: " + quantity
            color: "white"
        }
    }


//    Rectangle {
//        width: 500
//        height: 50

//        anchors.bottom: parent.bottom

//        color: "red"
//        anchors.horizontalCenter: parent.horizontalCenter

//        ListView {
//            id: view

//            model: tcpClientList.ui_tcpClients

//            width: parent.width
//            height: parent.height
//            focus: true
//            orientation: ListView.Horizontal
//            spacing: 10


//            delegate:
//                IpClient {
//                    tcpClient: modelData
//                }
//        }
//    }

    Rectangle {
        id: listViewWrapper
        width: parent.width
        height: parent.height/10
        anchors.bottom: parent.bottom
        anchors.left: parent.left
//        anchors.horizontalCenter: parent.horizontalCenter
        color: Style.colourTCPBar

        ListView {
            id: view
            anchors.fill: parent
            anchors.left: listViewWrapper.left
            anchors.leftMargin: 10
            orientation: ListView.Horizontal
            clip: true

            model: tcpClientList.ui_tcpClients

            delegate: Item {
                id: listDelegate

                property var view: ListView.view
                property var isCurrent: ListView.isCurrentItem

                width: listViewWrapper.width/(2*quantity)
                height: listViewWrapper.height

                Column {
                    anchors.fill: parent

                    Rectangle {
                        id: upRect
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: listDelegate.height/2

                        color: model.ui_isConnected.ui_value ? "red" : "blue"

                        border {
                            color: "black"
                            width: 1
                        }

                        Text {
                            anchors.centerIn: parent
                            renderType: Text.NativeRendering
    //                        text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                            text: model.ui_ip.ui_value
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: view.currentIndex = model.index
                        }
                    }

                    Rectangle {
                        anchors.top: upRect.bottom
                        anchors.left: upRect.left
                        anchors.right: upRect.right
                        height: listDelegate.height/2

                        color: model.ui_isConnected.ui_value ? "red" : "blue"

                        border {
                            color: "black"
                            width: 1
                        }

                        Text {
                            anchors.centerIn: parent
                            renderType: Text.NativeRendering
    //                        text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                            text: model.ui_ip.ui_value
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: view.currentIndex = model.index
                        }
                    }
                }

            }
        }
    }



}
