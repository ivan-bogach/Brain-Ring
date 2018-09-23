import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import components 1.0
import assets 1.0

Item {

    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left

    width: parent.width

    Rectangle {

        id: tcpBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: Style.colourNavigationBarBackground
        width: parent.width

        Column {
            width: parent.width
            TCPButton {
                btnText: "Старт"
                ontcpButtonClicked: {
                    masterController.ui_tcpController.
                    onNavigationButtonClicked: isCollapsed = true
                }
            }
            NavigationButton {
                btnText: "СОЗДАТЬ ИГРУ"
                onNavigationButtonClicked: {
                    masterController.ui_navigationController.goCreateGameView();
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

