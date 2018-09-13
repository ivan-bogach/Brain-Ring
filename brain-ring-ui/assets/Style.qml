pragma Singleton
import QtQuick 2.0

Item {
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


    Image {
        id: imageDashboardLoader
        source: "ring.jpg"
    }
}

