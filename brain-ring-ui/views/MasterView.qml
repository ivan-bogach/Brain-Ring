import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {

    Button {
        onClicked: contentFrame.replace("qrc:/views/DashboardView.qml");
    }


    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    StackView {
        id: contentFrame
        anchors.fill: parent
        initialItem: "qrc:/views/SplashView.qml"
    }
}
