import QtQuick 2.9
import QtQuick.Window 2.9
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.0
import "qrc:/components"

FluentWindow {
    id: window
    width: 1200
    minimumWidth: 1200
    height: 700
    minimumHeight: 700

    FileDialog {
        id: saveFileDialog
        fileMode: FileDialog.SaveFile
        currentFile: editor.currentFilePath
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Markdown files (*.md)"]
    }

    KeyTapEvent {
        id: exitAppEvent
        customKey: qsTr("Ctrl+Q")
        onClicked: {
            Qt.exit(0);
        }
    }

    KeyTapEvent {
        id: saveEvent
        customKey: qsTr("Ctrl+S")
        onClicked: {
        }
    }

    Rectangle {
        id: centralWidget
        anchors.fill: parent
        color: display.colorStyle ? "white" : "#24292e"

        // Behavior on color {
        //     ColorAnimation {
        //         duration: 280
        //     }
        // }

        SideBar {
            id: sideBar
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

        Rectangle  {
            id: line
            anchors.left: sideBar.right
            anchors.top: sideBar.top
            anchors.bottom: sideBar.bottom
            width: display.sideBarExpanded ? 1 : 0
            color: display.colorStyle ? "#40606060" : "#80000000"
        }

        Editor {
            id: mainEditor
            anchors.top: parent.top
            anchors.left: line.right
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            IconButton {
                id: sideBarButton
                anchors.left: mainEditor.left
                anchors.top: mainEditor.top
                icon: display.sideBarExpanded ? "qrc:/assets/folder-prohibited.svg" : "qrc:/assets/folder-open.svg"
                height: 35
                width: 35
                flat: true
                border.color: "transparent"
                onClicked: {
                    display.sideBarExpanded = !display.sideBarExpanded;
                }
            }

            IconButton {
                id: colorThemeButton
                anchors.right: mainEditor.right
                anchors.top: mainEditor.top
                icon: display.colorStyle ? "qrc:/assets/weather-sunny.svg" : "qrc:/assets/weather-moon.svg"
                height: 35
                width: 35
                flat: true
                border.color: "transparent"
                onClicked: {
                    display.colorStyle = !display.colorStyle;
                }
            }
        }
    }
}
