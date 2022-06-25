import QtQuick 2.15
import QtQuick.Controls 2.15

ItemDelegate {
    id: root

    readonly property int userId: model.id

    signal userClicked(int id)

    implicitWidth: 400
    implicitHeight: 70

    anchors.left: parent.left
    anchors.right: parent.right

    onClicked: { userClicked(userId) }

    Image {
        id: avatar
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        source: "qrc:/images/avatar_64.png"
        sourceSize.height: 48
        sourceSize.width: 48
        anchors.leftMargin: 10
    }

    Text {
        id: usernameText
        text: model.username
        anchors.left: avatar.right
        anchors.top: parent.top
        font.pixelSize: 16
        font.bold: true
        anchors.topMargin: 16
        anchors.leftMargin: 16
    }

    Text {
        id: text1
        x: 313
        y: 20
        text: root.userId
        font.pixelSize: 12
    }
}


