import QtQuick 2.15
import QtWebEngine 1.10

Rectangle {
    id: root
    color: display.colorStyle ? "white" : "black"
    
    Behavior on color {
        ColorAnimation {
            duration: 280
        }
    }

    WebEngineView {
        anchors.fill: parent
        url: "qrc:/web/index.html"
    }
}
