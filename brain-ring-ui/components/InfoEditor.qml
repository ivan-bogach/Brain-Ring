import QtQuick 2.0
import BR 1.0
import  assets 1.0

Panel {
    property Info info

    contentComponent:
        Column {
            id: column

// spacing : real - The spacing is the amount in pixels left empty between adjacent items
            spacing:  Style.sizeControlSpacing

            StringEditorSingleLine {
                stringDecorator: info.ui_building

                anchors.left: parent.left
                anchors.right: parent.right
            }

            StringEditorSingleLine {
                stringDecorator: info.ui_street

                anchors.left: parent.left
                anchors.right: parent.right
            }

            StringEditorSingleLine {
                stringDecorator: info.ui_city

                anchors.left: parent.left
                anchors.right: parent.right
            }

        }

}
