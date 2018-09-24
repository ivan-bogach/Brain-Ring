import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import components 1.0
import assets 1.0

Item {
    property bool isCollapsed: true

    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left

    width: isCollapsed ? Style.widthNavigationBarCollapsed : Style.widthNavigationBarExpanded

    Rectangle {
        Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml");
        id: navigationBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: Style.colourNavigationBarBackground
        width: parent.width

        Column {
            width: parent.width
            anchors.centerIn: parent

//            Text {
//                text: "БРЕЙН"
//                font.pixelSize: 50
//                color: "#ffffff"
//            }

//            Text {
//                text: "РИНГ"
//                font.pixelSize: 50
//                color: "#ffffff"
//            }
        }


        Column {
            width: parent.width
            anchors.centerIn: parent

            NavigationButton {
                btnText: "ИГРАТЬ"
                onNavigationButtonClicked: {
                    masterController.ui_navigationController.goStartGameView();
                    onNavigationButtonClicked: isCollapsed = true
                }
            }

            NavigationButton {

                btnText: "СОЗДАТЬ ИГРУ"
                onNavigationButtonClicked: {
                    masterController.ui_navigationController.goCreateGameView();
//                    masterController.ui_commandController
                    isCollapsed = true
                }
            }
            NavigationButton {
                btnText: "НАСТРОЙКИ"
                onNavigationButtonClicked: {
                    masterController.ui_navigationController.goSettingsView();
                    isCollapsed = true
                }
            }

        }

        NavigationButton {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Style.pixelSizeNavigationBarFont
            btnText: "ВЫХОД"
            onNavigationButtonClicked: {
                masterController.ui_navigationController.goDashboardView();
                isCollapsed = false
            }
        }
    }
}
