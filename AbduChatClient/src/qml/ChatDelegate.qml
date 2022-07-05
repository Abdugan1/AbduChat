import QtQuick 2.15
import QtQuick.Controls 2.15

import AbduChatLib 1.0

ItemDelegate {
    id: root

    function getChatUsername() {
        return chatClient.user.id === model.user_1_id ? model.user_2_username
                                                      : model.user_1_username
    }

    function calculateElapsedDays(date, today) {
        return Math.floor((today - date) / (24 * 60 * 60 * 1000))
    }

    function getDate(dateString) {
        var date = Date.fromLocaleString(Qt.locale(), dateString, dateFormat);
        var today = new Date();

        if (date.getFullYear() !== today.getFullYear()) {
            return date.toLocaleString(Qt.locale(), "dd.MM.yy");
        }
        if ((date.getDate() === today.getDate()) && (date.getMonth() === today.getMonth())) {
            return date.toLocaleString(Qt.locale(), "hh:mm");
        }
        if (calculateElapsedDays(date, today) <= 7) {
            return date.toLocaleString(Qt.locale(), "ddd");
        }
        if (date.getFullYear() === today.getFullYear()) {
            return date.toLocaleString(Qt.locale(), "dd MMM");
        }
    }

    Chat {
        id: chat
        chatId: model.chat_id
        type: model.chat_type
        user1Id: model.user_1_id
        user2Id: model.user_2_id
    }

    implicitWidth: 400
    implicitHeight: 70

    anchors.left: parent.left
    anchors.right: parent.right

    onClicked: {
        messagesTable.setCurrentChat(chat);
        chatClicked(usernameText.text)
    }

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
        text: getChatUsername()

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
        text: getDate(model.date)
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 14
        anchors.rightMargin: 11
    }
}
