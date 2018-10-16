import QtQuick 2.5
import assets 1.0

Item {

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
