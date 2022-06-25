import QtQuick 2.15
import QtQuick.Controls 2.15

ItemDelegate {
    id: root

    implicitWidth: 400
    implicitHeight: 70

    anchors.left: parent.left
    anchors.right: parent.right

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
        text: {
            console.log("my_id: " + getMyUserId());
            console.log("user_1_id: " + user_1_id);
            console.log("user_2_id: " + user_2_id);
            console.log("user_1_username: " + user_1_username);
            console.log("user_2_username: " + user_2_username);
            return getMyUserId() != user_1_id ? user_1_username : user_2_username;
        }

        anchors.left: avatar.right
        anchors.top: parent.top
        font.pixelSize: 16
        font.bold: true
        anchors.topMargin: 12
        anchors.leftMargin: 16
    }

    Text {
        id: lastMessage
        text: model.last_message
        anchors.left: avatar.right
        anchors.top: usernameText.bottom
        anchors.leftMargin: 16
        anchors.topMargin: 3
    }

    Text {
        id: sentTime
        text: date
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 14
        anchors.rightMargin: 11
    }
}
