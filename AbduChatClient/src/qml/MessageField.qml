import QtQuick 2.15
import QtQuick.Controls 2.15

TextArea {
    id: root

    signal sendClicked()

    wrapMode: Text.Wrap
    leftPadding: 12
    bottomPadding: 12
    topPadding: 12
    font.pointSize: 16
    placeholderText: qsTr("Message")
    selectByMouse: true
    rightPadding: 48

    Image {
        id: sendButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: "qrc:/images/send_32.png"
        anchors.bottomMargin: 8
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


