import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    anchors.fill: parent

    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        CheckBox {
            text: "Показывать вопросы?"
            checked: true
            onClicked: console.log(checkState)
        }
    }

}
