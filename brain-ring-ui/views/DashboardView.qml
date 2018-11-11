import QtQuick 2.5
import assets 1.0
import components 1.0
import BR 1.0

Item {
    Component.onCompleted: {
        mainWindow.visibility = "Windowed"
        navigationBar.isCollapsed = false
        masterController.ui_commandController.ui_gameViewContextCommands[1].executed()
        masterController.ui_commandController.ui_gameViewContextCommands[2].executed()
    }

    property bool staDan: true

    Image {
        anchors.fill: parent
        id: ring
        source: Style.imageDashboard
    }

    Image {
        id: trof
//        anchors.centerIn: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        source: staDan ? Style.imageTroSta : Style.imageTroDan;
        Timer {
            interval: 500; running: true; repeat: true
            onTriggered: staDan = !staDan
        }
    }
//    Timer {
//        interval: 3000
//        repeat: true
//        onTriggered: {
//            trof.source = Style.imageTroSta;
//            trof.source =Style.imageTroDan
//        }
//    }
}
