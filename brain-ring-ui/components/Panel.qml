import QtQuick 2.0
import assets 1.0

Item {
    property alias headerText: title.text

// sourceComponent : Component - This property holds the Component to instantiate.
// calling elements can inject their desired content at runtime
    property alias contentComponent: contentLoader.sourceComponent

//implicitHeight : real - Defines the natural width or height of the Item if no width or height is specified.
//Due to the dynamic nature of the content can`t set fixed size
    implicitWidth: parent.width
    implicitHeight: headerBackground.height + contentLoader.implicitHeight + (Style.sizeControlSpacing * 2) + Style.sizeShadowOffset


    Rectangle {
        id: shadow
        width: parent.width
        height: parent.height
        x: Style.sizeShadowOffset
        y: Style.sizeShadowOffset
        color: Style.colourShadow
    }

    Rectangle {
        id: headerBackground
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: Style.heightPanelHeader
        color: Style.colourPanelBackground

        Text {
            id: title
            text: "Set Me!"
            anchors.fill: parent
            anchors.margins:  Style.heightDataControls/4
            color: Style.colourPanelHeaderFont
            font.pixelSize: Style.pixelSizePanelHeader
            verticalAlignment: Qt.AlignVCenter
        }
    }

    Rectangle {
        id: contentBackground
        anchors.top: headerBackground.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: Style.colourPanelBackground
    }

//Allows dynamic loading of a subtree from a URL or Component
    Loader {
        id: contentLoader

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: Style.sizeControlSpacing
    }
}

