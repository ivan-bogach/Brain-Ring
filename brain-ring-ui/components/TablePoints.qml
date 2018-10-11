import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property TCPClientsList clientList

    Rectangle {
        anchors.fill: parent
        id: listViewWrapper
        color: Style.colourTCPBar

        ListView {
            id: view
            anchors.fill: parent
            anchors.left: listViewWrapper.left
            anchors.leftMargin: 10
            orientation: ListView.Horizontal
            clip: true

            model: clientList.ui_tcpClients

            delegate: Item {
                id: listDelegate

                property var view: ListView.view
                property var isCurrent: ListView.isCurrentItem

                width: listViewWrapper.width/(5*quantity)
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

