import QtQuick 2.15
import QtQuick.Controls 2.15

import AbduChatLib 1.0

ItemDelegate {
    id: root

    readonly property int chatId: model.chat_id

    function getChat() { return chat; }

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

    implicitWidth: 400
    implicitHeight: 70

    anchors.left: parent.left
    anchors.right: parent.right

    Image {
        id: avatar
        source: "qrc:/images/avatar_64.png"
        width: 64
        height: 64

        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: usernameText
        text: getChatUsername()
        font.pixelSize: 16
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 12
        anchors.left: avatar.right
        anchors.leftMargin: 16
    }

    Text {
        id: lastMessage
        text: model.last_message

        anchors.top: usernameText.bottom
        anchors.topMargin: 3
        anchors.left: avatar.right
        anchors.leftMargin: 16
    }

    Text {
        id: sentTime
        text: getDate(model.date)

        anchors.top: parent.top
        anchors.topMargin: 14
        anchors.right: parent.right
        anchors.rightMargin: 11
    }
}
