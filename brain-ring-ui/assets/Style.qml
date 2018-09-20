pragma Singleton
import QtQuick 2.0

Item {
    property alias fontAwesome: fontAwesomeLoader.name

    readonly property real sizeScreenMargine: 20
    readonly property color colourBackground: "#efefef"

    property alias imageDashboard: imageDashboardLoader.source

    readonly property real widthNavigationButton: widthNavigationBar - leftMarginNavigationButton
    readonly property real heightNavigationButton: 2.5*pixelSizeNavigationBarFont
    readonly property color colorNavigationButtonHover: "#202125"

    readonly property real leftMarginNavigationButton: pixelSizeNavigationBarFont*1.5

    readonly property real widthNavigationBar: 250
    readonly property color colourNavigationBarBackground: "#151618"
    readonly property color colourNavigationBarFont: "#ffffff"
    readonly property int pixelSizeNavigationBarFont: 21
    readonly property real widthNavigationBarCollapsed: 0
    readonly property real widthNavigationBarExpanded: widthNavigationButton

    readonly property color colourCommandBarBackground: "#cecece"
    readonly property color colourCommandBarFont: "#121212"
    readonly property color colourCommandBarFontDisabled: "#636363"
    readonly property real heightCommandBar: heightCommandButton
    readonly property int pixelSizeCommandBarIcon: 32
    readonly property int pixelSizeCommandBarText: 12
    readonly property real widthCommandButton: 80
    readonly property real heightCommandButton: widthCommandButton

    readonly property color colourDataControlsBackground: "#ffffff"
    readonly property color colourDataControlsFont: "#121212"
    readonly property int pexelSizeDataControls: 18
    readonly property real widthDataControls: 400
    readonly property real heightDataControls: 40

    readonly property real sizeControlSpacing:	10
    readonly property color colourPanelBackground:	"#ffffff"
    readonly property color colourPanelBackgroundHover:	"#ececec"
    readonly property color	colourPanelHeaderBackground:	"#131313"
    readonly property color	colourPanelHeaderFont:	"#ffffff"
    readonly property color	colourPanelFont:	"#131313"
    readonly property int pixelSizePanelHeader:	18
    readonly property real heightPanelHeader:	40
    readonly property real sizeShadowOffset:	5
    readonly property color colourShadow:	"#dedede"

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.ttf"
    }

    Image {
        id: imageDashboardLoader
        source: "ring.jpg"
    }
}

