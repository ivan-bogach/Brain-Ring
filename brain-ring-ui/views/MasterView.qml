import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import components 1.0
import assets 1.0

Window {
    visible: true
    width: 723
    height: 520
    title: qsTr("Hello World")
//    Item replace(target, item, properties, operation)

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
        Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml");
        id: navigationBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: Style.widthNavigationBar
        color: "#151618"

        Column {
            NavigationButton {
                btnText: "Играть"
            }
            NavigationButton {
                btnText: "Создать игру"
            }
            NavigationButton {
                btnText: "Настройки"
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
