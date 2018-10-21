import QtQuick 2.5
import assets 1.0
import components 1.0
import BR 1.0

Item {

//    Component.onCompleted: {
////        masterController.ui_commandController.ui_gameViewContextCommands[1].executed()
//        masterController.ui_commandController.ui_gameViewContextCommands[2].executed()
//    }

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    Image {
        anchors.fill: parent
        id: gameOver
        source: Style.imageGameOver
    }
}
