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
            NavigationButton {
                btnText: "ИГРАТЬ"
                onNavigationButtonClicked: {
                    masterController.ui_navigationController.goGameView();
                    onNavigationButtonClicked: isCollapsed = true
                }
            }
            NavigationButton {
                btnText: "СОЗДАТЬ ИГРУ"
                onNavigationButtonClicked: {
                    masterController.ui_navigationController.goCreateGameView();
                    masterController.ui_commandController.
                    isCollapsed = true
                }
            }
            NavigationButton {
                btnText: "НАСТРОЙКИ"
                onNavigationButtonClicked: {
                    masterController.ui_navigationController.goFindGameView();
                    isCollapsed = true
                }
            }

            NavigationButton {
                btnText: "ВЫХОД"
                onNavigationButtonClicked: {
                    masterController.ui_navigationController.goDashboardView();
                    isCollapsed = false
                }
            }
        }
    }
}

