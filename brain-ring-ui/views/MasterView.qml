import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import components 1.0
import assets 1.0


Window {

    //=========================================================================
        onActiveFocusItemChanged: print("activeFocusItem", activeFocusItem)//==
    //=========================================================================

//    Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml")

    visible: true
    width: 1080
    height: 780
    title: qsTr("Брейн ринг")

    Text {
        text: masterController.ui_welcomeMessage
    }



    Connections {
        target: masterController.ui_navigationController
        onGoCreateGameView: contentFrame.replace("qrc:/views/CreateGameView.qml")
        onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")
        onGoSettingsView: contentFrame.replace("qrc:/views/SettingsView.qml")
        onGoStartGameView: contentFrame.replace("qrc:/views/StartGameView.qml", {selectedGame: game})

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
    }
}
