import QtQuick 2.9
import QtWebEngine 1.5
import QtWebChannel 1.0
import Qt.labs.platform 1.1
import "qrc:/components"

Rectangle {
    id: root
    
    WebEngineView {
        id: previewWebView
        anchors.fill: parent
        url: "qrc:/web/preview.html"

        webChannel: WebChannel {
            id: webChannel
            Component.onCompleted: {
                webChannel.registerObject("displayManager", display);
                webChannel.registerObject("editorManager", editor);
            }
        }
    }
}
