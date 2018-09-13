import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import assets 1.0

Item {
    property alias btnText: text.text


    width: Style.widthNavigationButton
    height: Style.heightNavigationButton
    Rectangle{
        id: background
        anchors.fill: parent
        color: Style.colourNavigationBarBackground

        Row {
            Text {
                id: text
                color: Style.colourNavigationBarFont
                width: Style.widthNavigationButton
                height: Style.pixelSizeNavigationBarFont
                text: "SET ME!!!"

            }
        }
    }
}


