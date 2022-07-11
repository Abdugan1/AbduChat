import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    id: root

    property color backgroundColor: "black"
    property color borderColor: "black"
    property int borderWidth: 0
    property real borderRadius: 10.0
    property color hoverColor: "#7ee6a1"

    property color textColor: "white"

    implicitWidth: 350
    implicitHeight: 54

    states: [
        State {
            name: "hoveredState"
            when: hovered
            PropertyChanges {
                target: root
                backgroundColor: hoverColor
            }
        }
    ]

    background: Rectangle {
        id: backgroundRectangle

        color: root.backgroundColor
        border.color: root.borderColor
        border.width: root.borderWidth
        radius: root.borderRadius
    }

    contentItem: Item {
        Text {
            id: buttonText
            text: root.text
            color: root.textColor
            anchors.centerIn: parent
        }
    }
}

/*##^##
Designer {
    D{i:0;height:50;width:300}
}
##^##*/
