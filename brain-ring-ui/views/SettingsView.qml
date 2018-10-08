import QtQuick 2.0
import QtQuick.Controls 1.4
Item {
    anchors.fill: parent

    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 27
        CheckBox {
            text: "Показывать вопросы?"
            checked: true
            onClicked: console.log(checkedState)
        }

        SpinBox {
            value: 5
        }
    }

}
