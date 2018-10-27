import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
//    id: waitPlayers
    property GamePlay gameP
    property int numPlayersFromSettings

    property string bgColor: masterController.ui_settings.ui_bgColor.ui_value
    property string txtColor: masterController.ui_settings.ui_txtColor.ui_value

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
            color:bgColor
            radius: listViewRect.width/(numPlayersFromSettings + 1)

            Text {
                id: topTop
                anchors.centerIn: parent
                color:  txtColor
                text: (modelData.ui_isConnected.ui_value === "true")  ? "участник " + modelData.ui_number.ui_value : ""
            }
        }
    }
}
