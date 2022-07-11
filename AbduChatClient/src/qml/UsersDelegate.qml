import QtQuick 2.15
import QtQuick.Controls 2.15

ItemDelegate {
    id: root

    readonly property int userId: model.id

    signal userClicked(int userId)

    implicitWidth: 400
    implicitHeight: 70

    anchors.left: parent.left
    anchors.right: parent.right

    onClicked: { userClicked(root.userId) }

    Image {
        id: avatar
        source: "qrc:/images/avatar_64.png"
        sourceSize.height: 48
        sourceSize.width: 48

        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: usernameText
        text: model.username
        font.pixelSize: 16
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 16
        anchors.left: avatar.right
        anchors.leftMargin: 16
    }
}


