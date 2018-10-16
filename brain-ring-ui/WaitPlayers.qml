import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    id: waitPlayers
    property GamePlay gameP
    property int numPlayersFromSettings

    anchors.centerIn: parent
    width: parent.width
    height: parent.height

    ListView {
        anchors.fill: parent
        orientation: ListView.Horizontal
        spacing: 10

        model: gameP.ui_players

        delegate: Rectangle {
            width: listViewRect.width/(numPlayersFromSettings + 1)
            height: listViewRect.width/(numPlayersFromSettings + 1)
            color: (modelData.ui_isConnected.ui_value === "true")  ? "#FF9243" : Style.colourTCPBar
            border.color: (modelData.ui_isConnected.ui_value === "true") ? "#6EB3FE" : Style.colourTCPBar
            border.width: 3
            radius: listViewRect.width/(numPlayersFromSettings + 1)

            Text {
                id: topTop
                anchors.centerIn: parent
                color:  "#7432EE"
                text: (modelData.ui_isConnected.ui_value === "true")  ? "кнопка " + modelData.ui_number.ui_value : ""
            }
        }
    }
}
