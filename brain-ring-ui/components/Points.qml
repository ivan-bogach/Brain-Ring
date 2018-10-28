import QtQuick 2.0
import assets 1.0
import BR 1.0

Item {
    property GamePlay gamePlay
    property int numPlayersFromSettings
    property StringDecorator winnerNumber

    property string bgColor: masterController.ui_settings.ui_bgColor.ui_value
    property string txtColor: masterController.ui_settings.ui_txtColor.ui_value

    anchors.fill: parent

    Rectangle {

        width: parent.width*0.9
        height: parent.height/7

        color: bgColor

        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/20
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: listViewRect
            anchors.fill: parent
            color: bgColor


            ListView {
                id: lw
                anchors.fill: parent
                orientation: ListView.Horizontal

                header: Rectangle {
                    id: header

                    width: topHeader.width + 10
                    height: parent.height
                    color: Style.colourPointsHeaderBackground

                    Column {
                        anchors.centerIn: parent
                        width: parent.width
                        height: parent.height

                        Rectangle {
                            id: topRectHeader
                            anchors.top: parent.top
                            anchors.left: parent.left

                            height: parent.height/2
                            width: parent.width
                            color: Style.colourPointsBorder

                            Text {
                                id: topHeader
                                anchors.centerIn: parent
                                color:  Style.colourPointsText
                                font.pixelSize: parent.height > 50 ? 30 : 15
                                text: "Участник"
                            }
                        }

                        Rectangle {
                            id: bottomRectHeader
                            anchors.top: topRectHeader.bottom
                            anchors.right: parent.right
                            color: Style.colourPointsBackground

                            height: parent.height/2
                            width: parent.width

                            Text {
                                id: bottomHeader
                                anchors.centerIn: parent
                                color: Style.colourPointsText
                                font.pixelSize: parent.height > 50 ? 30 : 15
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
                    color: Style.colourPointsBackground
                    anchors.leftMargin: 10

                    Column {
                        id: listView
                        anchors.centerIn: parent
                        width: parent.width
                        height: parent.height



                        Rectangle {
                            id: topRect
                            anchors.top: parent.top
                            anchors.left: parent.left

                            height: parent.height/2
                            width: parent.width
                            color: Style.colourPointsBorder

                            Rectangle {
                                id: winnerTextRect
                                color: "transparent"
                                anchors.horizontalCenter: top.horizontalCenter
                                anchors.bottom: top.top
                                width: winnerText.width
                                height: winnerText.height

                                Text {
                                    id: winnerText
                                    anchors.centerIn: parent
                                    font.family: Style.brFont
                                    color: "#26c794"
                                    font.pixelSize: parent.height > 50 ? 70 : 45
                                    text: (modelData.ui_isLeader.ui_value === "true") ? "A" : ""
                                }

                            }
                            ParallelAnimation {

                                NumberAnimation {
                                    target: winnerTextRect
                                    property: "scale"
                                    from: 0.1;
                                    to: 3.0
                                    duration: 2000
                                    easing.type: Easing.InOutQuad
                                }

                                NumberAnimation {
                                    target: winnerTextRect
                                    property: "opacity"
                                    from: 0.3
                                    to: 1
                                    duration: 2000
                                }
                                running: true
                                loops: 1
                            }

                            Text {
                                id: top
                                anchors.centerIn: parent
                                color:  (modelData.ui_isLeader.ui_value === "true") ? "#26c794" : Style.colourPointsText
                                font.family: "Helvetica"
                                font.pixelSize: parent.height > 50 ? 30 : 15
                                text: modelData.ui_number.ui_value
                            }
                        }

                        Rectangle {
                            id: bottomRect
                            anchors.top: topRect.bottom
                            anchors.right: parent.right
                            color: Style.colourPointsBackground


                            height: parent.height/2
                            width: parent.width

                            Rectangle {
                                width: parent.width*0.7
                                height: parent.height*0.7
                                anchors.centerIn: parent

                                color: Style.colourPointsBackground

                                radius: (height>50) ? 3 : 0
                                border.color: (modelData.ui_number.ui_value === winnerNumber.ui_value) ? Style.colourPointsWinnerBorder : Style.colourPointsBorder
                                border.width: 2

                                Text {
                                    id: bottom
                                    anchors.centerIn: parent
                                    color: Style.colourPointsText
                                    font.family: "Helvetica"
                                    font.pixelSize: parent.height > 50 ? 30 : 15
                                    text: modelData.ui_points.ui_value
                                }
                            }

                        }
                    }
                }
            }
        }
    }
}

