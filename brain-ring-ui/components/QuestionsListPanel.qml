import QtQuick 2.0

Item {
     property alias contentComponent: contentLoader.sourceComponent

    implicitWidth: parent.width
    implicitHeight: contentLoader.implicitHeight


    Loader {

        id: contentLoader

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
    }
}

