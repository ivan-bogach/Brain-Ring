import QtQuick 2.0

Item {
    anchors.fill: parent

    focus: true
    Keys.onEscapePressed: {
        contentFrame.replace("qrc:/views/DashboardView.qml")
    }

    Text {
        id: questionText
        font.pixelSize: 30
        text: "Тут вопрос."
    }
}

