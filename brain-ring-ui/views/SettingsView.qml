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

    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 27
        CheckBox {
            text: "Показывать вопросы?"
            checked: askQuestion.ui_value == 2 ? true : false
            onClicked: {
                settings.ui_askQuestions.ui_value = checkedState
                console.log(checkedState)
            }
        }

        SpinBox {
            value: quantity.ui_value
            onValueChanged: {
                settings.ui_quantity.ui_value = value
                console.log(value)
            }
        }

        SettingsBar {
            id: settingsBar
            commandList: masterController.ui_commandController.ui_settingsViewContextCommands
        }
    }
}
