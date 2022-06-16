import QtQuick 2.15
import QtQuick.Controls 2.15

ItemDelegate {
    id: root

    implicitWidth: 400
    implicitHeight: 70

    width: parent.width

    onClicked: { userClicked(model.username, model.id) }

    Image {
        id: avatar
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        source: "qrc:/images/avatar_64.png"
        anchors.leftMargin: 10
        sourceSize.height: 64
        sourceSize.width: 64
        width: 64
        height: 64
    }

    Text {
        id: usernameText
        text: model.username
        anchors.left: avatar.right
        anchors.top: parent.top
        font.pixelSize: 16
        font.bold: true
        anchors.topMargin: 12
        anchors.leftMargin: 16
    }

    Text {
        id: lastMessage
        text: "Here should be the last message"
        anchors.left: avatar.right
        anchors.top: usernameText.bottom
        anchors.leftMargin: 16
        anchors.topMargin: 3
    }

    Text {
        id: sentTime
        text: "9:41"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 14
        anchors.rightMargin: 11
    }
}
