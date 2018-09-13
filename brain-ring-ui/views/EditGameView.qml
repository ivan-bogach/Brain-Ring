import QtQuick 2.5
import assets 1.0

Item {
    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: "#f4c842"
        Text {
            anchors.centerIn: parent
            id: splashviewtext
            text: "Edit Game"
        }
    }
}
