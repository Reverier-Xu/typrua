import QtQuick 2.9
import QtQuick.Window 2.9
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.0
import "qrc:/components"

FluentWindow {
    id: window
    width: 1260
    minimumWidth: 1260
    height: 700
    minimumHeight: 700

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
            editor.save();
        }
    }

    FileDialog {
        id: saveFileDialog
        fileMode: FileDialog.SaveFile
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Markdown (*.md)"]

        onAccepted: {
            // console.log(editor.getLocalFilePath(exportFileDialog.file.toString()));
            editor.saveAs(editor.getLocalFilePath(saveFileDialog.file.toString()));
        }

        Connections {
            target: editor
            function onSavePathRequested() {
                saveFileDialog.open();
            }
        }
    }

    FileDialog {
        id: exportFileDialog
        fileMode: FileDialog.SaveFile
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["PDF (*.pdf)"]

        onAccepted: {
            // console.log(editor.getLocalFilePath(exportFileDialog.file.toString()));
            editor.exportAs(editor.getLocalFilePath(exportFileDialog.file.toString()));
        }
    }

    FileDialog {
        id: openFileDialog
        fileMode: FileDialog.OpenFile
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Markdown (*.md)"]

        onAccepted: {
            // console.log(editor.getLocalFilePath(openFileDialog.file.toString()));
            editor.open(editor.getLocalFilePath(openFileDialog.file.toString()));
        }

        Connections {
            target: editor
            function onOpenFilePathRequested() {
                openFileDialog.open();
            }
        }

    }

    Rectangle {
        id: centralWidget
        anchors.fill: parent
        color: display.colorStyle ? "white" : "#24292e"

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

        EditorPage {
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
                contentColor: display.sideBarExpanded ? display.themeColor : display.contentColor
                height: 35
                width: 35
                flat: true
                border.color: "transparent"
                onClicked: {
                    display.sideBarExpanded = !display.sideBarExpanded;
                }
            }

            IconButton {
                id: outlineButton
                anchors.left: sideBarButton.right
                anchors.top: mainEditor.top
                icon: "qrc:/assets/timeline.svg"
                contentColor: display.outlineExpanded ? display.themeColor : display.contentColor
                height: 35
                width: 35
                flat: true
                border.color: "transparent"
                onClicked: {
                    display.outlineExpanded = !display.outlineExpanded;
                }
            }
        }

        PreviewPage {
            id: previewPage
            anchors.fill: mainEditor
            visible: false
        }
    }
}
