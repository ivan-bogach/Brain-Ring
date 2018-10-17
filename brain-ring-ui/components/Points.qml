import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property GamePlay gamePlay
    property int numPlayersFromSettings

    anchors.fill: parent

    Rectangle {

        width: parent.width*0.9
        height: parent.height/7

//        radius: parent.width/7

        color: Style.colourTCPBar
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/20
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: listViewRect
            anchors.fill: parent
            color: Style.colourTCPBar

            ListView {
                anchors.fill: parent
                anchors.top: headerRect.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                orientation: ListView.Horizontal
                spacing: 10

                header: Rectangle {
                    id: header
//                    width: listViewRect.width/(numPlayersFromSettings)
                    width: topHeader.width + 10
                    height: parent.height
                    color: Style.colourTCPBar

                    Column {
//                        id: listView
                        anchors.centerIn: parent
                        width: parent.width
                        height: parent.height

                        Rectangle {
                            id: topRectHeader
                            anchors.top: parent.top
                            anchors.left: parent.left

                            border.color: "#05E4B5"
                            border.width: 2

                            height: parent.height/2
                            width: parent.width
                            color: Style.colourTCPBar

                            Text {
                                id: topHeader
                                anchors.centerIn: parent
                                color:  "#05E4B5"
                                font.italic: true
                                font.pixelSize: parent.height > 50 ? 30 : 15
                                text: "Участник"
                            }
                        }

                        Rectangle {
                            id: bottomRectHeader
                            anchors.top: topRectHeader.bottom
                            anchors.right: parent.right
                            color: Style.colourTCPBar

                            border.color: "#05E4B5"
                            border.width: 2

                            height: parent.height/2
                            width: parent.width


                            Text {
                                id: bottomHeader
                                anchors.centerIn: parent
                                color: "#05E4B5"
                                font.pixelSize: parent.height > 50 ? 30 : 15
                                font.italic: true
                                text: "Очки"
                            }
                        }
                    }
                }

//===================================================================================================

                model: gamePlay.ui_players

                delegate: Rectangle {
                    id: delegate
                    width: listViewRect.width/12
                    height: parent.height
                    color: Style.colourTCPBar

                    Column {
                        id: listView
                        anchors.centerIn: parent
                        width: parent.width
                        height: parent.height

                        Rectangle {
                            id: topRect
                            anchors.top: parent.top
                            anchors.left: parent.left

                            border.color: "#05E4B5"
                            border.width: 2

                            height: parent.height/2
                            width: parent.width
                            color: Style.colourTCPBar

                            Text {
                                id: top
                                anchors.centerIn: parent
                                color:  "#05E4B5"
                                font.italic: true
                                font.family: "Helvetica"
                                font.pixelSize: parent.height > 50 ? 50 : 25
                                text: modelData.ui_number.ui_value
                            }
                        }

                        Rectangle {
                            id: bottomRect
                            anchors.top: topRect.bottom
                            anchors.right: parent.right
                            color: Style.colourTCPBar

                            border.color: "#05E4B5"
                            border.width: 2

                            height: parent.height/2
                            width: parent.width


                            Text {
                                id: bottom
                                anchors.centerIn: parent
                                color: "#05E4B5"
                                font.family: "Helvetica"
                                font.pixelSize: parent.height > 50 ? 50 : 25
                                font.italic: true
                                text: modelData.ui_points.ui_value
                            }
                        }
                    }
                }
            }
        }
    }
}

