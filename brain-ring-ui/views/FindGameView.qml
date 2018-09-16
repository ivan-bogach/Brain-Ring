import QtQuick 2.5
import assets 1.0

Item {
    focus: true
    Keys.onEscapePressed: navigationBar.isCollapsed = !navigationBar.isCollapsed
    Rectangle {
        anchors.fill: parent
        color: "#f4c842"
        Text {
           anchors.centerIn: parent
           text: "Find Game"
        }
    }
}
