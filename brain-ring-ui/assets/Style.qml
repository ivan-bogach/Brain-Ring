pragma Singleton
import QtQuick 2.0

Item {
    property alias fontAwesome: fontAwesomeLoader.name
    property alias brFont: brFontLoader.name

    property alias imageDashboard: imageDashboardLoader.source
    property alias imageLogo: logoLoader.source
    property alias imageGameOver: gameOverLoader.source
    property alias imageTroSta: troSta.source
    property alias imageTroDan: troDan.source

    readonly property real sizeScreenMargine: 20
    readonly property color colourBackground: "#efefef"

    readonly property color colourSettingsBackground: "#aabfca"

    readonly property color colourGameViewsBackground: "#062e2e"
    readonly property color colourGameViewsText: "#da967f"

    readonly property color colourPointsBackground: "#18191d"
    readonly property color colourPointsHeaderBackground: "#18191d"
    readonly property color colourPointsBorder: "#232428"
    readonly property color colourPointsWinnerBorder: "#0080ff"
    readonly property color colourPointsText: "#cccccc"

    readonly property color colourPointsGameOverText: "#feff04"
    readonly property color colourPointsGameOverHeaderText: "#f8b800"

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
    readonly property int pixelSizeDataControls: 18
    readonly property real widthDataControlsNum: 30
    readonly property real widthDataControls: 300
    readonly property real heightDataControls: 30

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

    readonly property color colourTCPBar:	"#0F1120"
    readonly property color colourTCPButton:	"#dedede"
    readonly property real widthTCPButton: 30

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.ttf"
    }

    FontLoader {
        id: brFontLoader
        source: "qrc:/assets/brain_ring_font.otf"
    }

    Image {
        id: imageDashboardLoader
        source: "ring.jpg"
    }


    Image {
        id: logoLoader
        source: "logo.png"
    }

    Image {
        id: gameOverLoader
        source: "gameover.png"
    }

    Image {
        id: troSta
        source: "sta.png"
    }

    Image {
        id: troDan
        source: "dan.png"
    }
}

