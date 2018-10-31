import QtQuick 2.5
import assets 1.0
import components 1.0
import BR 1.0

Item {
    property GamePlay gamePlay: masterController.ui_gamePlay
    property Settings settings: masterController.ui_settings

    property string bgColor: masterController.ui_settings.ui_bgColor.ui_value
    property string txtColor: masterController.ui_settings.ui_txtColor.ui_value

    Component.onCompleted: {
        masterController.ui_commandController.ui_gameViewContextCommands[1].executed()
    }

     Keys.onPressed: {
         if (event.key === Qt.Key_Escape)
         {
             masterController.ui_navigationController.goGameOverView()
         }
     }

    Rectangle {
        id:background

        anchors.fill: parent
        color: bgColor

        Rectangle {
            id: titleRect
            width: parent.width
            height: parent.height/7
            anchors.top: parent.top
            color: bgColor

            Text {
                id: titleText
                anchors.centerIn: parent
                font.pixelSize: 50
                color: txtColor
                text: qsTr("Итоговый счет")
            }
        }

        Rectangle {
            id: listViewRect
            width: parent.width
            anchors.top: titleRect.bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            color: bgColor

            ListView {
                spacing: 5
                orientation: ListView.Vertical
                anchors.fill: parent

                header: Rectangle {
                    id: headerRect
                    width: parent.width * 0.75
                    height: listViewRect.height/12

                    anchors.top: listViewRect.top
                    anchors.horizontalCenter: parent.horizontalCenter

                    color: bgColor
                    border.color: txtColor
                    border.width: 1

                    Row {
                        anchors.fill: parent

                        Rectangle{
                            id: headerNumberRect
                            width: parent.width/3
                            height: parent.height

                            anchors.left: parent.left
                            anchors.top: parent.top

                            color: bgColor
                            border.color: txtColor
                            border.width: 1


                            Text{
                                id: headerNumberText
                                anchors.centerIn: parent
                                font.bold: true
                                color: txtColor
                                font.pixelSize: 25
                                text: "Участник"
                            }
                        }

                        Rectangle{
                            id: headerAttemptsRect
                            width: parent.width/3
                            height: parent.height

                            anchors.left: headerNumberRect.right
                            anchors.top: parent.top

                            color: bgColor
                            border.color: txtColor
                            border.width: 1

                            Text{
                                id: headerattemptsText

                                font.bold: true
                                color: txtColor
                                anchors.centerIn: parent
                                font.pixelSize: 25
                                text: "Ответов"
                            }
                        }

                        Rectangle{
                            id: headerPointsRect
                            width: parent.width/3
                            height: parent.height

                            anchors.left: headerAttemptsRect.right

                            anchors.top: parent.top

                            color: bgColor
                            border.color: txtColor
                            border.width: 1

                            Text{
                                id: headerPointsText
                                font.pixelSize: 25
                                font.bold: true
                                color: txtColor
                                anchors.centerIn: parent
                                text: "Правильных"
                            }
                        }


                    }

                }

                model: gamePlay.ui_players

                delegate:Rectangle {
                        width: parent.width * 0.75
                        height: listViewRect.height/(settings.ui_quantity.ui_value + 2)

//                        border.width:
//                        border.color: "red"
                        anchors.horizontalCenter: parent.horizontalCenter

                        color: bgColor
                        Row {
                            anchors.fill: parent

                            Rectangle{
                                id: numberRect
                                width: parent.width/3
                                height: parent.height

                                anchors.left: parent.left
                                anchors.top: parent.top

                                color: bgColor
                                border.color: txtColor
                                border.width: 1


                                Text{
                                    id: numberText
                                    anchors.centerIn: parent

                                    color: txtColor
                                    font.pixelSize: (modelData.ui_isLeader.ui_value === "true") ? 70 : 25
                                    text: modelData.ui_number.ui_value
                                }
                            }

                            Rectangle{
                                id: attemptsRect
                                width: parent.width/3
                                height: parent.height

                                anchors.left: numberRect.right

                                anchors.top: parent.top

                                color: bgColor
                                border.color: txtColor
                                border.width: 1

                                Text{
                                    id: attemptsText

                                    color: txtColor
                                    anchors.centerIn: parent
                                    font.pixelSize: 25
                                    text: modelData.ui_attempts.ui_value
                                }
                            }

                            Rectangle{
                                id: pointsRect
                                width: parent.width/3
                                height: parent.height

                                anchors.left: attemptsRect.right

                                anchors.top: parent.top

                                color: bgColor
                                border.color: txtColor
                                border.width: 1

                                Text{
                                    id: pointsText

                                    color: txtColor
                                    anchors.centerIn: parent
                                    font.pixelSize: 25
                                    text: modelData.ui_points.ui_value
                                }
                            }


                        }

                    }
            }
        }

    }
}
