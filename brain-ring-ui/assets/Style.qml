pragma Singleton
import QtQuick 2.0

Item {
    readonly property color colourBackground: "#efefef"
    property alias imageDashboard: imageDashboardLoader.source

    Image {
        id: imageDashboardLoader
        source: "ring.jpg"
    }
}

