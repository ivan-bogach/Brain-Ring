import QtQuick 2.0
import BR 1.0

Item {
    property GamePlay gamePlay
    property int numPlayersFromSettings

    anchors.fill: parent

    Rectangle {
        id: listViewRect
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 300

        ListView {
            anchors.fill: parent
            orientation: ListView.Horizontal
            spacing: 10

            model: gamePlay.ui_players

            delegate: Rectangle {
                width: listViewRect.width/(numPlayersFromSettings + 1)
                height: listViewRect.width/(numPlayersFromSettings + 1)
                color: "#FF9243"
                border.color: "#6EB3FE"
                border.width: 3
//                    radius: listViewRect.width/(numPlayersFromSettings + 1)

                Text {
                    id: top
                    anchors.centerIn: parent
                    color:  "#7432EE"
                    text: modelData.ui_number.ui_value
                }
                Text {
                    id: bottom
                    anchors.top: top.bottom
                    color:  "#7432EE"
                    text: modelData.ui_points.ui_value
                }
            }
        }
    }

}

