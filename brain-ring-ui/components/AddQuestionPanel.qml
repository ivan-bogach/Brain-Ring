import QtQuick 2.0
import QtQuick.Controls 1.4
import BR 1.0

Item {
    property StringDecorator stringDecoratorNumber
    property StringDecorator stringDecoratorText
    property alias  commandList: commandRepeater.model

    width: parent.width

    focus: true

    Grid {
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 3
        spacing: 9
//first raw
        Rectangle {
            width: 50
            height: 15

            Text {
                id: numberLabel
                font.pixelSize: 15
                text: qsTr("Номер:")
            }
        }

        Rectangle {
            width: parent.width*0.8
            height: 15

            Text {
                id: textLabel
                font.pixelSize: 15
                text: qsTr("Вопрос:")
            }
        }
        Rectangle {
            width: 15
            height: 15

            Text {
                id: saveLabel
                font.pixelSize: 15
                text: qsTr("")
            }
        }
//second raw
        Rectangle {
            width: 50
            height: 50

            border.width: 1

            TextField {
                id: numValue
                validator: RegExpValidator { regExp: /[0-9]+/ }
                anchors.fill: parent
                font.pixelSize: 15
                horizontalAlignment: TextInput.AlignHCenter
                text: stringDecoratorNumber.ui_value



                verticalAlignment: Qt.AlignVCenter

            }
            clip: true
            //establishes a dependency between the properties of two different objects;
            Binding {
                target: stringDecoratorNumber
                property: "ui_value"
                value: numValue.text
            }
        }

        Rectangle {
            width: parent.width*0.8
            height: 50

            border.width: 1

            TextField {
                id: textValue
                anchors.fill: parent
                horizontalAlignment: TextInput.AlignLeft
                font.pixelSize: 15
                text: stringDecoratorText.ui_value
            }
            clip: true

            //establishes a dependency between the properties of two different objects;
            Binding {
                target: stringDecoratorText
                property: "ui_value"
                value: textValue.text
            }
        }

        Rectangle {
            height: 50
            anchors.left: textValue.right
            anchors.leftMargin: 10
            width: 50

            Repeater {
                id: commandRepeater
                delegate: CommandButton {
                    command: modelData
                }
            }
        }


    }

}

