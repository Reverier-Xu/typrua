import QtQuick 2.9
import "qrc:/components"

Rectangle {
    id: root
    color: "transparent"
    width: 280
    clip: true
    property bool expanded: display.sideBarExpanded
    state: expanded? "Expanded" : "Folded"

    Behavior on width {
        NumberAnimation {
            duration: 300
            easing.type: Easing.OutExpo
        }
    }

    PushButton {
        id: titleButton
        height: 32
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        showIcon: true
        contentColor: display.contentColor
        icon: "qrc:/assets/document.svg"
        text: qsTr("Files")
        flat: true
        enabled: false
    }

    IconButton {
        id: openFileIconButton
        anchors.right: titleButton.right
        anchors.top: titleButton.top
        anchors.bottom: titleButton.bottom
        icon: "qrc:/assets/open.svg"
        flat: true
        width: height
    }

    SearchBox {
        id: globalSearchBox
        height: 28
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: titleButton.bottom
        anchors.margins: 12
        placeholder: qsTr("Filter...")
    }

    Text {
        id: nothingFoundText
        anchors.top: globalSearchBox.bottom
        anchors.topMargin: 36
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Nothing here.")
        font.pixelSize: 16
        font.bold: true
        color: "#808080"
    }

    PushButton {
        id: openFileButton
        height: 32
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: nothingFoundText.bottom
        anchors.topMargin: 24
        width: parent.width - 24
        showIcon: false
        text: qsTr("Open File")
    }

    PushButton {
        id: openFolderButton
        height: 32
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: openFileButton.bottom
        anchors.topMargin: 12
        width: parent.width - 24
        showIcon: false
        text: qsTr("Open Folder")
    }

    ListView {
        id: libraryList
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: globalSearchBox.bottom
        anchors.topMargin: 12
        anchors.bottom: parent.top
        anchors.bottomMargin: 12

        delegate: ActiveTab {
            width: ListView.view.width
            height: 36
            anchors.topMargin: 3
            flat: true
            border.color: "transparent"
            showIcon: true
            icon: "qrc:/assets/document-edit.svg"
            isTabActive: index === libraryList.currentIndex
        }
    }

    states: [
        State {
            name: "Expanded"
            PropertyChanges {
                target: root
                width: 280
            }
        },
        State {
            name: "Folded"
            PropertyChanges {
                target: root
                width: 0
            }
        }
    ]
}
