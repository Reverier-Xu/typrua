import QtQuick 2.9
import QtQuick.Controls 2.4

ScrollBar {
    id: scroll
    width: 6
    background: Rectangle {
        implicitWidth: 6
        radius: width / 2
        color: "transparent"
    }
    contentItem: Rectangle {
        implicitWidth: 6
        implicitHeight: 100
        radius: width / 2
        color: scroll.pressed? "#808080" : (scroll.active? "#80808080":"transparent")
        // Behavior on color {
        //     ColorAnimation { duration: 200 }
        // }
    }
}
