import QtQuick 2.9
import QtWebEngine 1.5
import QtWebChannel 1.0

Rectangle {
    id: root
    color: display.colorStyle ? "white" : "#24292e"

    // Behavior on color {
    //     ColorAnimation {
    //         duration: 280
    //     }
    // }

    WebEngineView {
        anchors.fill: parent
        url: "qrc:/web/index.html"

        webChannel: WebChannel {
            id: webChannel
            Component.onCompleted: {
                webChannel.registerObject("displayManager", display);
                webChannel.registerObject("editorManager", editor);
            }
        }
    }
}
