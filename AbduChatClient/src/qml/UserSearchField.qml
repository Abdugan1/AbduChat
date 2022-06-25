import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: root
    font.pointSize: 14

    placeholderText: qsTr("Search")
    selectByMouse: true

    implicitHeight: 43
    implicitWidth: 300
    rightPadding: 32

//    background: Rectangle {
//        border.color: "black"
//    }
    background: {}

    Image {
        id: clearButton
        visible: root.text != ""
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        source: "qrc:/images/x_16.png"
        anchors.rightMargin: 8

        MouseArea {
            anchors.fill: parent
            onClicked: root.text = ""
        }
    }
}
