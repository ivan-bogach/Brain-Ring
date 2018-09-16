import QtQuick 2.0
import BR 1.0
import assets 1.0

Item {
    property  StringDecorator stringDecorator
    height: width > textLabel.width + textValue.width ? Style.heightDataControls : Style.heightDataControls * 2

//Positions its children side by side, wrapping as necessary
    Flow {
        anchors.fill: parent

        Rectangle {
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourBackground
            Text {
                id: textLabel
                anchors.fill: parent
                anchors.margins: Style.heightDataControls / 4

//                text: stringDecorator.ui_label

                color: Style.colourDataControlsFont
                font.pixelSize:  Style.pexelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Rectangle {
            id: background
            width: Style.widthDataControls
            height: Style.heightDataControls
            color: Style.colourDataControlsBackground
            border.width: 1
            border.color: Style.colourDataControlsFont

            TextInput {
                id: textValue
                anchors.fill: parent
                anchors.margins: Style.heightDataControls / 4

                text: stringDecorator.ui_value

                Keys.onEscapePressed: {
                    focus = false
                }

                color: Style.colourDataControlsFont
                font.pixelSize: Style.pexelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }

        }

//establishes a dependency between the properties of two different objects;
        Binding {
            target: stringDecorator
            property: "ui_value"
            value: textValue.text
        }

    }
}
