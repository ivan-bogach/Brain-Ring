import QtQuick 2.5
import assets 1.0
import components 1.0
import BR 1.0

Item {
    property GamePlay gamePlay: masterController.ui_gamePlay
    property Settings settings: masterController.ui_settings

    Rectangle {
        id:background

        anchors.fill: parent
        color: Style.colourGameViewsBackground

//        border.color: "black"
//        border.width: 1

        Rectangle {
            id: titleRect
            width: parent.width
            height: parent.height/5
            anchors.top: parent.top
            color: Style.colourGameViewsBackground


//            border.color: "orange"
//            border.width: 1

            Text {
                id: titleText
                anchors.centerIn: parent
                font.pixelSize: 50
                color: Style.colourGameViewsText
                text: qsTr("Итоговый счет")
            }
        }

        Rectangle {
            id: listViewRect
            width: parent.width
            anchors.top: titleRect.bottom
            anchors.bottom: parent.bottom


//            border.color: "pink"
//            border.width: 1

            color: Style.colourGameViewsBackground

            ListView {
                spacing: 5
                orientation: ListView.Vertical
                anchors.fill: parent

                model: gamePlay.ui_players

                delegate:Rectangle {
                        width: parent.width
                        height: listViewRect.height/settings.ui_quantity.ui_value

                        border.color: "red"
                        border.width: 1

                        Row {
                            anchors.fill: parent
                            Rectangle{
                                id: numberRect
                                width: parent.width/2
                                anchors.left: parent.left
                                anchors.top: parent.top

                                border.color: "blue"
                                border.width: 1


                                Text{
                                    id: numberText
                                    anchors.centerIn: parent

                                    font.pixelSize: 25
                                    text: "number" + modelData.ui_number.ui_value
                                }
                            }

                            Rectangle{
                                width: parent.width/2

                                anchors.left: numberRect.right
                                anchors.top: parent.top

                                border.color: "yellow"
                                border.width: 1

                                Text{
                                    id: pointsText

                                    anchors.centerIn: parent
                                    font.pixelSize: 25
                                    text: "points" + modelData.ui_points.ui_value
                                }
                            }


                        }

                    }
            }
        }

    }
}
