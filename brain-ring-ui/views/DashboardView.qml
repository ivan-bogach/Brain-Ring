import QtQuick 2.5
import assets 1.0
import components 1.0

Item {
    Component.onCompleted: {
        mainWindow.visibility = "Windowed"
        navigationBar.isCollapsed = false
    }

    Image {
        anchors.fill: parent
        id: ring
        source: Style.imageDashboard
    }
}
