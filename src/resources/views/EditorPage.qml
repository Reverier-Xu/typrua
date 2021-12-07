import QtQuick 2.9
import QtWebEngine 1.5
import QtWebChannel 1.0
import Qt.labs.platform 1.1
import "qrc:/components"

Rectangle {
    id: root
    color: display.colorStyle ? "white" : "#24292e"

    property var downloads

    // Behavior on color {
    //     ColorAnimation {
    //         duration: 280
    //     }
    // }

    Rectangle {
        id: loadProgressRect
        anchors.top: parent.top
        anchors.left: parent.left
        height: 3
        color: display.themeColor
        width: parent.width * webView.loadProgress / 100
        opacity: webView.loading
    }

    Loader {
        id: loader
        anchors.centerIn: parent
        opacity: webView.loading
    }

    Rectangle {
        id: fileProgressRect
        anchors.top: parent.top
        anchors.left: parent.left
        height: 3
        color: display.themeColor
        property int progress: 100
        width: parent.width * progress / 100
        visible: progress !== 100
    }

    Timer {
        id: reloadTimer
        interval: 10
        running: false
        repeat: true
        onTriggered: {
            fileProgressRect.progress = root.downloads.receivedBytes / root.downloads.totalBytes
        }
    }

    WebEngineView {
        id: webView
        anchors.fill: parent
        url: "qrc:/web/index.html"
        settings.javascriptCanAccessClipboard: true

        webChannel: WebChannel {
            id: webChannel
            Component.onCompleted: {
                webChannel.registerObject("displayManager", display);
                webChannel.registerObject("editorManager", editor);
            }
        }

        Component.onCompleted: {
            // profile.downloadRequested.connect(webView.onDownloadRequested)
            // profile.downloadFinished.connect(webView.onDownloadFinished)
        }
    }
        
    DropArea {
        anchors.fill: parent
        onDropped: {
            // TODO: should handle multiple files
            if (drop.hasUrls) {
                // for(var i = 0; i < drop.urls.length; i++) {
                //     // console.log(drop.urls.length);
                //     queue.playExternMedia(drop.urls[i]);
                // }
                editor.handleDrop(drop.urls[0]);
            }
        }
    }
}
