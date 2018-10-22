import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.0
import BR 1.0
import components 1.0
import assets 1.0

Item {
    property color bgColor: "#062e2e"
    property color txtColor: "#da967f"

    Component.onCompleted: {
        masterController.ui_commandController.ui_gameViewContextCommands[1].executed()
        masterController.ui_commandController.ui_gameViewContextCommands[2].executed()
        masterController.ui_commandController.ui_settingsViewContextCommands[0].executed()

        if ( masterController.ui_settings.ui_bgColor.ui_value !== "" )
        {
            bgColor = masterController.ui_settings.ui_bgColor.ui_value;
        }
        else
        {
            settings.ui_bgColor.ui_value = "#062e2e"
        }

        if ( masterController.ui_settings.ui_txtColor.ui_value !== "" )
        {
            txtColor = masterController.ui_settings.ui_txtColor.ui_value;
        }
        else
        {
            settings.ui_txtColor.ui_value = "#da967f"
        }
    }

    focus: true
    Keys.onReturnPressed: {
        commandList: masterController.ui_commandController.ui_settingsViewContextCommands[1].executed()
        console.log("-----------------------------------------------------------------------------")
    }

    property StringDecorator stringDecoratorQuantity
    property IntDecorator intDecoratorAskQuestions
    property Settings settings: masterController.ui_settings

    property IntDecorator askQuestion: masterController.ui_settings.ui_askQuestions
    property IntDecorator quantity: masterController.ui_settings.ui_quantity

    anchors.fill: parent

    Rectangle {
        id:background
        anchors.fill: parent
        color: Style.colourSettingsBackground

        ColorDialog {
            id: colorBackgroundDialog
            title: "Выберите цвет фона"
            onAccepted: {
                console.log("You chose: " + colorBackgroundDialog.color)
                settings.ui_bgColor.ui_value = colorBackgroundDialog.color
                bgColor = colorBackgroundDialog.color
            }
        }
        ColorDialog {
            id: colorTextDialog
            title: "Выберите цвет фона"
            onAccepted: {
                console.log("You chose: " + colorTextDialog.color)
                settings.ui_txtColor.ui_value = colorTextDialog.color
                txtColor = colorTextDialog.color
            }
        }

        Row{
            id: row
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 27

            Rectangle {
                id: backgroundColorButton
                color: bgColor
                height: row.height
                width: defaultColorTxt.width

                radius: 3

                Text {
                    id: bgColorTxt
                    anchors.centerIn: parent
                    text: qsTr("Цвет фона")
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onClicked: {
                        colorBackgroundDialog.open()
                    }
                }
            }

            Rectangle {
                id: textColorButton
                color: txtColor
                height: row.height
                width: defaultColorTxt.width

                radius: 3

                Text {
                    id: textColorTxt
                    anchors.centerIn: parent
                    text: qsTr("Цвет текста")
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onClicked: {
                        colorTextDialog.open()
                    }
                }
            }

            Rectangle {
                id: defaultColorsButton
                color: txtColor
                height: row.height
                width: defaultColorTxt.width

                radius: 3

                Rectangle {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    width: parent.width/2
                    height: parent.height
                    color: bgColor
                }

                Rectangle {
                    anchors.top: parent.top
                    anchors.right: parent.right
                    width: parent.width/2
                    height: parent.height
                    color: txtColor
                }

                Text {
                    id: defaultColorTxt
                    anchors.centerIn: parent
                    text: qsTr("Сбросить цвета")
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onClicked: {
                        bgColor = "#062e2e"
                        settings.ui_bgColor.ui_value = "#062e2e"
                        txtColor= "#da967f"
                        settings.ui_txtColor.ui_value = "#da967f"
                    }
                }
            }

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
}
