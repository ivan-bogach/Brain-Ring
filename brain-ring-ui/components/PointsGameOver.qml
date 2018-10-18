import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property GamePlay gamePlay
    property int numPlayersFromSettings

    anchors.fill: parent

    Rectangle {

        width: parent.width/4
        height: parent.height*0.9

        color: "transparent"
        anchors.right: parent.right
        anchors.rightMargin: parent.width/20
        anchors.verticalCenter: parent.verticalCenter

        Rectangle {
            id: listViewRect

            anchors.fill: parent

            color: "transparent"

            ListView {
                anchors.fill: parent

                orientation: ListView.Vertical
                spacing: 10

                header: Rectangle {
                    id: headerRect

                    width: listViewRect.width
                    height: top.height

                    anchors.right: listViewRect.right
                    color: "transparent"

                    border.color: "blue"
                    border.width: 1

                    Column {
                        anchors.fill: parent


                        Rectangle {
                            id: points

                            width: parent.width
                            height: parent.height/2

                            anchors.top: headerRect.top
                            anchors.left: headerRect.left

                            Text {
                                id: pointsHeader
                                anchors.centerIn: parent
                                color:  Style.colourPointsGameOverHeaderText
                                font.italic: true
                                font.family: "Helvetica"
                                font.pixelSize: 30
                                text: "Счет"
                            }
                        }

                        Row {
                            id: headerRow

                            width: parent.width
                            height: parent.height/2

                            anchors.right: parent.right
                            anchors.top: points.bottom
                            spacing: 30

                            Rectangle {
                                id: topHeaderRect

                                height: parent.height
                                width: parent.width/2

                                anchors.top: parent.top
                                anchors.left: parent.left

                                color: "transparent"

                                Text {
                                    id: topHeader
                                    anchors.centerIn: parent
                                    color:  Style.colourPointsGameOverHeaderText
                                    font.italic: true
                                    font.family: "Helvetica"
                                    font.pixelSize: 30
                                    text: "Участник"
                                }
                            }

                            Rectangle {
                                id: bottomHeaderRect

                                height: parent.height
                                width: parent.width/2

                                anchors.top: parent.top
                                anchors.left: topHeaderRect.right
                                color: "transparent"

                                Text {
                                    id: bottomHeader
                                    anchors.centerIn: parent
                                    color: Style.colourPointsGameOverHeaderText
                                    font.family: "Helvetica"
                                    font.pixelSize: 30
                                    font.italic: true
                                    text: "Очки"
                                }
                            }
                        }
                    }

                }

//===================================================================================================

                model: gamePlay.ui_players

                delegate: Rectangle {
                    id: delegate

                    width: listViewRect.width
                    height: listViewRect.height/( numPlayersFromSettings + 2 )

                    anchors.right: listViewRect.right
//                    anchors.top: headerRect.bottom

                    color: "transparent"

                    border.color: "red"
                    border.width: 1

                    Row {
                        id: listView

                        width: parent.width
                        height: parent.height

                        anchors.right: parent.right
                        spacing: 30

                        Rectangle {
                            id: topRect
                            anchors.top: parent.top
                            anchors.left: parent.left

                            height: top.height
                            width: parent.width/2

                            color: "transparent"

                            Text {
                                id: top

                                font.pixelSize: 100/numPlayersFromSettings

                                anchors.centerIn: parent
                                font.italic: true
                                font.bold: true
                                font.family: "Helvetica"
                                color:  Style.colourPointsGameOverText
                                text: modelData.ui_number.ui_value
                            }
                        }

                        Rectangle {
                            id: bottomRect

                            height: bottom.height
                            width: parent.width/2

                            anchors.top: parent.top
                            anchors.left: topRect.right
                            color: "transparent"


                            Text {
                                id: bottom

                                font.pixelSize: 100/numPlayersFromSettings

                                anchors.centerIn: parent
                                color: Style.colourPointsGameOverText
                                font.family: "Bitstream Charter"
                                font.bold: true
                                font.italic: true
                                style: Text.Raised
                                text: modelData.ui_points.ui_value
                            }
                        }
                    }
                }
            }
        }
    }
}

