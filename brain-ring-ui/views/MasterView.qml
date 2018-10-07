import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import components 1.0
import assets 1.0

Window {

//=========================================================================
//    onActiveFocusItemChanged: print("activeFocusItem", activeFocusItem)//==
//=========================================================================

    visible: true
    width: 920
    height: 550
    title: qsTr("Brain Ring")
//    Item replace(target, item, properties, operation)

//A Connections object creates a connection to a QML signal
//the usual way is to create an "on<Signal>" handler (SLOT) that reacts when a signal is received
    Connections {
//target : Object - This property holds the object that sends the signal.
        target: masterController.ui_navigationController
//        onGoGameView: contentFrame.replace("qrc:/views/GameView.qml", {selectedGame: game})
        onGoGameView: contentFrame.replace("qrc:/views/GameView.qml")
        onGoCreateGameView: contentFrame.replace("qrc:/views/CreateGameView.qml")
        onGoEditGameView: contentFrame.replace("qrc:/views/CreateGameView.qml")

        onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")
        onGoEditQuestionView: contentFrame.replace("qrc:/views/EditQuestionView.qml", {selectedGame: game})
        onGoFindGameView: contentFrame.replace("qrc:/views/FindGameView.qml")
    }

    NavigationBar {
        id: navigationBar
        isCollapsed: false

        focus: true
        Keys.onEscapePressed: {
            isCollapsed = !isCollapsed
        }
    }

    StackView {
        id: contentFrame
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: navigationBar.right
        initialItem: "qrc:/views/SplashView.qml"

// For FindGameView
        Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed
    }
}



