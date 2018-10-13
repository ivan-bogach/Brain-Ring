import QtQuick 2.0
import QtQuick.Controls 1.4
import BR 1.0
import components 1.0

Item {
    Component.onCompleted: masterController.ui_commandController.ui_settingsViewContextCommands[0].executed()

    property StringDecorator stringDecoratorQuantity
    property IntDecorator intDecoratorAskQuestions
    property Settings settings: masterController.ui_settings

    property IntDecorator askQuestion: masterController.ui_settings.ui_askQuestions
    property IntDecorator quantity: masterController.ui_settings.ui_quantity

    anchors.fill: parent

    Row{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 27

        CheckBox {
            focus: true
            text: "Показывать вопросы?"
            anchors.verticalCenter: spin.verticalCenter
            checked: askQuestion.ui_value == 2 ? true : false
            onClicked: {
                settings.ui_askQuestions.ui_value = checkedState
                console.log(checkedState)
            }
        }

        SpinBox {
            id: spin
            value: quantity.ui_value
            onValueChanged: {
                settings.ui_quantity.ui_value = value
                console.log(value)
            }
        }
    }

    Rectangle {
        id: rect
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter

        SettingsBar {
            anchors.fill: parent
            id: settingsBar

            commandList: masterController.ui_commandController.ui_settingsViewContextCommands
        }
    }

}
