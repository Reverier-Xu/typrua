import QtQuick 2.9
import QtWebEngine 1.0

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
