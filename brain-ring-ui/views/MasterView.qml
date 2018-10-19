import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import components 1.0
import assets 1.0

Window {
    id: mainWindow
//=========================================================================
    onActiveFocusItemChanged: print("activeFocusItem", activeFocusItem)//==
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
        onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")
        onGoSettingsView: contentFrame.replace("qrc:/views/SettingsView.qml")
        onGoCreateGameView: contentFrame.replace("qrc:/views/CreateGameView.qml")
        onGoGameView: contentFrame.replace("qrc:/views/GameView.qml")
        onGoGameQuestionView: contentFrame.replace("qrc:/views/GameQuestionView.qml", {question: game})
        onGoGameAnswerView: contentFrame.replace("qrc:/views/GameAnswerView.qml", {playerNumber: number})
        onGoPlayerWinView: contentFrame.replace("qrc:/views/PlayerWinView.qml", {playerNumber: number})
        onGoEmptyQuestionsListView: contentFrame.replace("qrc:/views/EmptyQuestionsListView.qml")
        onGoGameOverView: contentFrame.replace("qrc:/views/GameOverView.qml")
    }

    NavigationBar {
        id: navigationBar
        isCollapsed: false
    }

    StackView {
        id: contentFrame
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: navigationBar.right
        initialItem: "qrc:/views/SplashView.qml"

        onCurrentItemChanged: {
                currentItem.forceActiveFocus()
        }
    }
}



