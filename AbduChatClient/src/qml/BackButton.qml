import QtQuick 2.0

Item {
    id: root

    implicitHeight: 24
    implicitWidth: 24

    Image {
        id: image
        anchors.fill: parent
        source: "qrc:/images/back_24.png"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: { stackView.pop() }
    }
}




