import QtQuick 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.15
import Qt.labs.platform 1.1
import "../components"

Rectangle {
    id: root
    color: display.colorStyle ? "white" : "black"
    Behavior on opacity {
        NumberAnimation {
            duration: 100
        }
    }
    Behavior on color {
        ColorAnimation {
            duration: 280
        }
    }

    height: 32

    IconButton {
        id: closeButton
        icon: "qrc:/assets/dismiss.svg"
        iconSize: 16
        pressedColor: "#ccee0000"
        hoverColor: "#aaff0000"
        border.color: "transparent"
        flat: true
        anchors.right: parent.right
        anchors.top: parent.top
        width: 54
        height: 32
        onClicked: {
            window.close();
        }
    }

    IconButton {
        id: maximizeButton
        icon: window.visibility === Window.Windowed ? "qrc:/assets/maximize.svg" : "qrc:/assets/restore.svg"
        iconSize: 16
        flat: true
        anchors.right: closeButton.left
        anchors.top: parent.top
        border.color: "transparent"
        width: 54
        height: 32
        onClicked: {
            if (window.visibility === Window.Maximized || window.visibility === Window.FullScreen)
                window.showNormal();
            else
                window.showMaximized();
        }
    }

    IconButton {
        id: minimizeButton
        icon: "qrc:/assets/subtract.svg"
        iconSize: 16
        flat: true
        anchors.right: maximizeButton.left
        anchors.top: parent.top
        border.color: "transparent"
        width: 54
        height: 32
        onClicked: {
            window.showMinimized();
        }
    }

    IconButton {
        id: colorStyleButton
        icon: display.colorStyle ? "qrc:/assets/weather-sunny.svg" : "qrc:/assets/weather-moon.svg"
        iconSize: 16
        flat: true
        anchors.right: minimizeButton.left
        anchors.top: parent.top
        border.color: "transparent"
        width: 54
        height: 32
        onClicked: {
            display.colorStyle = !display.colorStyle
        }
    }

    PushButton {
        id: titleButton
        icon: "qrc:/assets/navigation.svg"
        text: qsTr("TypRua!")
        anchors.left: parent.left
        anchors.top: parent.top
        height: 32
        flat: true
        border.color: "transparent"
        onClicked: {
            display.sideBarExpanded = !display.sideBarExpanded;
        }
    }

    TapHandler {
        onTapped: if (tapCount === 2) toggleMaximized();
        gesturePolicy: TapHandler.DragThreshold
    }

    DragHandler {
        grabPermissions: TapHandler.DragThreshold
        onActiveChanged: {
            if (active) {
                window.startSystemMove();
            }
        }
    }
}
