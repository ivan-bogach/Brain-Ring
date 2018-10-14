import QtQuick 2.0
import BR 1.0

Item {
    property GamePlay gameP

    anchors.fill: parent
    ListView {
        anchors.fill: parent
        orientation: ListView.Horizontal
        spacing: 10

        model: gameP.ui_players

        delegate: Rectangle {
            width: mainRect.width/10
            Text {
                id: topTop
                anchors.top: parent.top
                anchors.topMargin: 30
                text: modelData.ui_number.ui_value
            }
            Text {
                id: topDown
                anchors.top:topTop.bottom
                anchors.topMargin: 30
                text: modelData.ui_number.ui_label
            }

            Text {
                id: middleTop
                anchors.top: topDown.bottom
                anchors.topMargin: 30
                text: modelData.ui_points.ui_value
            }
            Text {
                id: middleDown
                anchors.top:middleTop.bottom
                anchors.topMargin: 30
                text: modelData.ui_points.ui_value
            }
            Text {
                id: downTop
                anchors.top: middleDown.bottom
                anchors.topMargin: 30
                text: modelData.ui_isConnected.ui_value
            }
            Text {
                id: downDown
                anchors.top:downTop.bottom
                anchors.topMargin: 30
                text: modelData.ui_isConnected.ui_label
            }
        }
    }

}
