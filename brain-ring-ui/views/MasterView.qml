import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
//    Item replace(target, item, properties, operation)
    Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml");

//A Connections object creates a connection to a QML signal
//the usual way is to create an "on<Signal>" handler (SLOT) that reacts when a signal is received
    Connections {
//target : Object - This property holds the object that sends the signal.
        target: masterController.ui_navigationController
        onGoGameView: contentFrame.replace("qrc:/views/GameView.qml", {selectedGame: game})
        onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")
        onGoCreateGameView: contentFrame.replace("qrc:/views/CreateGameView.qml")
        onGoEditGameView: contentFrame.replace("qrc:/views/EditGameView.qml", {selectedGame: game})
        onGoFindGameView: contentFrame.replace("qrc:/views/FindGameView.qml")
    }

    Rectangle {
        id: navigationBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 100
        color: "#000000"

        Column {
            Button {
                text: "Dashboard"
                onClicked: masterController.ui_navigationController.goDasboardView()
            }
        }
    }

    StackView {
        id: contentFrame
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: navigationBar.right
        initialItem: "qrc:/views/SplashView.qml"
    }
}
