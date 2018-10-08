import QtQuick 2.0
import QtQuick.Controls 1.4
import BR 1.0
import components 1.0

Item {
    property StringDecorator stringDecoratorQuantity
    property IntDecorator intDecoratorAskQuestions
    property Settings settings: masterController.ui_settings

    Component.onCompleted: {
        settings.ui_askQuestions.ui_value = "2"
        settings.ui_quantity.ui_value = 5
        console.log(settings.ui_askQuestions.ui_value)
        console.log(settings.ui_quantity.ui_value)
    }

    anchors.fill: parent

    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 27
        CheckBox {
            text: "Показывать вопросы?"
            checked: true
            onClicked: {
                settings.ui_askQuestions.ui_value = checkedState
                console.log(checkedState)
            }
        }

        SpinBox {
            value: 5
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
