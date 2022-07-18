import QtQuick 2.15
import QtQuick.Controls 2.15

TextArea {
    id: root

    signal sendClicked()

    selectByMouse: true
    placeholderText: qsTr("Message")
    wrapMode: Text.Wrap
    font.pointSize: 16

    topPadding: 12
    leftPadding: 12
    bottomPadding: 12
    rightPadding: 48

    background: Rectangle { id: backgroundRect }

    Image {
        id: sendButton
        source: "qrc:/images/send_32.png"

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (root.text.trim() != "")
                    root.sendClicked()
            }
        }
    }
}


