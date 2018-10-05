import QtQuick 2.0
import QtQuick.Controls 1.4
import BR 1.0

Item {
    property StringDecorator stringDecoratorNumber
    property StringDecorator stringDecoratorText

    width: parent.width

    focus: true

    Grid {
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
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
            width: parent.width*0.9
            height: 15

            Text {
                id: textLabel
                font.pixelSize: 15
                text: qsTr("Вопрос:")
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
            width: parent.width*0.9
            height: 50

            border.width: 1

            TextField {
                id: textValue
                anchors.fill: parent
                horizontalAlignment: TextInput.AlignHCenter
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


    }

}

