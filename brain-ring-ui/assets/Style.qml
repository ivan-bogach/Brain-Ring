pragma Singleton
import QtQuick 2.5

Item {
    property alias fontAwesome: fontAwesomeLoader.name

    property alias imageDashboard: imageDashboardLoader.source

    readonly property color colourBackground: "#f4c842"

    readonly property real widthNavigationButton: widthNavigationBar - leftMarginNavigationButton
    readonly property real heightNavigationButton: 2.5*pixelSizeNavigationBarFont
    readonly property color colorNavigationButtonHover: "#202125"
    readonly property real leftMarginNavigationButton: pixelSizeNavigationBarFont*1.5


    readonly property real widthNavigationBar: 350
    readonly property color colourNavigationBarBackground: "#151618"
    readonly property color colourNavigationBarFont: "#ffffff"
    readonly property int pixelSizeNavigationBarFont: 30
    readonly property real widthNavigationBarCollapsed: 0
    readonly property real widthNavigationBarExpanded: widthNavigationButton

    readonly property real widthCommandButton: 80
    readonly property real heightCommandButton: widthCommandButton

    readonly property color colourCommandBarBackground: "#cecece"
    readonly property color colourCommandBarFont: "#121212"
    readonly property color colourCommandBarFontDisabled: "#636363"
    readonly property real heightCommandBar: heightCommandButton
    readonly property int pixelSizeCommandBarIcon: 32
    readonly property int pixelSizeCommandBarText: 12



    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.ttf"
    }

    Image {
        id: imageDashboardLoader
        source: "brains.jpg"
    }

}
