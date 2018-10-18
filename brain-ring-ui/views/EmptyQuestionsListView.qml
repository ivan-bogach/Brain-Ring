import QtQuick 2.5
import assets 1.0
import components 1.0
import BR 1.0

Item {
    property GamePlay gamePlayInPlayerWin: masterController.ui_gamePlay
    property int  numberPlayersFromSettings: masterController.ui_settings.ui_quantity.ui_value

        Component.onDestruction: masterController.ui_commandController.ui_gameViewContextCommands[1].executed()

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
