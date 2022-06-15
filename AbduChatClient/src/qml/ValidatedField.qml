import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: root

    property color backgroundColor: "white"
    property color borderColor: "black"
    property int borderWidth: 1
    property real borderRadius: 0.0

    property alias iconSource: icon.source
    property alias iconSourceSize: icon.sourceSize


    implicitHeight: 40
    implicitWidth: 40
    leftPadding: 42
    placeholderTextColor: "grey"
    selectByMouse: true

    background: Rectangle {
        id: backgroundRectangle

        color: backgroundColor
        border.color: borderColor
        border.width: borderWidth
        radius: borderRadius

        Image {
            id: icon

            source: iconSource
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            sourceSize.height: 20
        }
    }
}
