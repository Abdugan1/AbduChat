import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: root

    property color backgroundColor: "white"
    property color borderColor: "black"
    property int borderWidth: 1
    property real borderRadius: 0.0
    property color hoverColor: "grey"

    property color textColor: "black"
    states: [
        State {
            name: "hoveredState"
            when: hovered
            PropertyChanges {
                target: root
                backgroundColor: "#7ee6a1"
            }
        }
    ]

    implicitWidth: 40
    implicitHeight: 40

    background: Rectangle {
        id: backgroundRectangle

        color: backgroundColor
        border.color: borderColor
        border.width: borderWidth
        radius: borderRadius
    }

    contentItem: Item {
        Text {
            id: buttonText
            text: root.text
            color: textColor
            anchors.centerIn: parent
        }
    }
}

/*##^##
Designer {
    D{i:0;height:50;width:300}
}
##^##*/
