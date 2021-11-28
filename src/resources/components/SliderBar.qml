import QtQuick 2.15

Rectangle {
    id: root
    property double currentValue: 0
    property double dragValue: 0
    property double lineHeight: 2
    property bool onDragging: false
    height: 16
    color: "transparent"

    Behavior on color {
        ColorAnimation {
            duration: 200
        }
    }

    Behavior on lineHeight {
        NumberAnimation {
            duration: 200
        }
    }

    signal startDragging();
    signal endDragging(double finalValue);

    Rectangle {
        id: progressPart
        height: root.lineHeight
        radius: height / 2
        color: display.themeColor
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: onDragging? (currentValue > dragValue ? dragPoint.left : currentProgressPoint.left)
                                : currentProgressPoint.left
        anchors.rightMargin: 4
    }

    Rectangle {
        id: differPart
        height: root.lineHeight
        radius: height / 2
        visible: root.onDragging
        color: display.alertColor
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: currentValue > dragValue ? dragPoint.right : currentProgressPoint.right
        anchors.right: currentValue > dragValue ? currentProgressPoint.left : dragPoint.left
        anchors.leftMargin: 4
        anchors.rightMargin: 4
    }

    Rectangle {
        id: unExplorePart
        height: root.lineHeight
        radius: height / 2
        color: display.colorStyle? "#80606060" : "#80909090"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: onDragging? (currentValue > dragValue ? currentProgressPoint.right : dragPoint.right)
                               : currentProgressPoint.right
        anchors.right: parent.right
        anchors.leftMargin: 4
    }

    Rectangle {
        id: currentProgressPoint
        width: 16
        height: 16
        radius: 8
        color: "transparent"
        border.width: 4
        Behavior on color {
            ColorAnimation {
                duration: 200
            }
        }
        border.color: display.themeColor
        Behavior on border.color {
            ColorAnimation {
                duration: 200
            }
        }
        anchors.verticalCenter: parent.verticalCenter
        x: (root.width - 16) * currentValue
    }

    Rectangle {
        id: dragPoint
        width: 16
        height: 16
        radius: 8
        color: "transparent"
        Behavior on color {
            ColorAnimation {
                duration: 200
            }
        }
        border.width: 4
        border.color: display.alertColor
        Behavior on border.color {
            ColorAnimation {
                duration: 200
            }
        }
        anchors.verticalCenter: parent.verticalCenter
        visible: root.onDragging
        x: (root.width - 16) * dragValue
    }

    MouseArea {
        id: hoverArea
        anchors.fill: parent

        hoverEnabled: true

        onEntered: {
            if (!pressed)
                parent.state = "Hovering";
        }

        onExited: {
            if (!pressed)
                parent.state = "Normal";
        }

        onPressed: {
            root.state = "Pressed";
            root.onDragging = true;
            if (root.onDragging) {
                let val = 0;
                if (mouseX - 8 < 0)
                    val = 0;
                else if (mouseX - 8 > root.width - 16)
                    val = 1;
                else
                    val = (mouseX - 8) / (root.width - 16);
                if (controlAnim.running)
                    controlAnim.stop();
                controlAnim.from = currentValue;
                controlAnim.to = val;
                controlAnim.start();
            }
            root.startDragging();
        }

        onReleased: {
            if (containsMouse)
                parent.state = "Hovering";
            else
                parent.state = "Normal";
            root.onDragging = false;
            root.endDragging(root.dragValue);
        }

        onPositionChanged: {
            if (root.onDragging) {
                let val = 0;
                if (mouseX - 8 < 0)
                    val = 0;
                else if (mouseX - 8 > root.width - 16)
                    val = 1;
                else
                    val = (mouseX - 8) / (root.width - 16);
                if(controlAnim.running)
                    controlAnim.stop();
                root.dragValue = val;
            }
        }
    }

    NumberAnimation {
        id: controlAnim
        target: root
        property: "dragValue"
        duration: 150
        easing.type: Easing.OutExpo
    }

    states: [
        State {
            name: "Hovering"
            PropertyChanges {
                target: currentProgressPoint
                color: border.color
            }
            PropertyChanges {
                target: dragPoint
                color: border.color
            }
            PropertyChanges {
                target: root
                lineHeight: 4
            }
        },
        State {
            name: "Normal"
            PropertyChanges {
                target: currentProgressPoint
                color: "transparent"
            }
            PropertyChanges {
                target: dragPoint
                color: "transparent"
            }
            PropertyChanges {
                target: root
                lineHeight: 2
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: currentProgressPoint
                color: border.color
            }
            PropertyChanges {
                target: dragPoint
                color: display.alertColor
                border.color: display.alertColor
            }
            PropertyChanges {
                target: root
                lineHeight: 4
            }
        }
    ]
}
