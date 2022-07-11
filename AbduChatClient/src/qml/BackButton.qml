import QtQuick 2.0

Item {
    id: root

    implicitHeight: 24
    implicitWidth: 24

    Image {
        id: image
        source: "qrc:/images/back_24.png"

        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea
        onClicked: { stackView.pop() }

        anchors.fill: parent
    }
}




