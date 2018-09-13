pragma Singleton
import QtQuick 2.0

Item {
    readonly property color colourBackground: "#efefef"
    property alias imageDashboard: imageDashboardLoader.source



    readonly property real widthNavigationBar: 215
    readonly property color colourNavigationBarBackground: "#151618"
    readonly property color colourNavigationBarFont: "#ffffff"
    readonly property int pixelSizeNavigationBarFont: 42
    readonly property real leftMarginNavigationButton: pixelSizeNavigationBarFont*2.5
    readonly property real widthNavigationButton: widthNavigationBar - leftMarginNavigationButton
    readonly property real heightNavigationButton: 3*pixelSizeNavigationBarFont


    Image {
        id: imageDashboardLoader
        source: "ring.jpg"
    }
}

