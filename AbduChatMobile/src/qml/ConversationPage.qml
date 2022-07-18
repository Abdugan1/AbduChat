import QtQuick 2.15
import QtQuick.Controls 2.15

import AbduChatLib 1.0

Page {
    id: root

    signal sendButtonClicked(string messageText)

    function getChatUsername() {
        if (chatClient.user.id === -1)
            return ""
        return chatClient.user.id === messagesTable.currentChat.user1Id
                ? usersTable.getUsername(messagesTable.currentChat.user2Id)
                : usersTable.getUsername(messagesTable.currentChat.user1Id)
    }

    implicitWidth: 440
    implicitHeight: 760
    visible: true

    header: ToolBar {
        height: 43
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0

        BackButton {
             anchors.left: parent.left
             anchors.leftMargin: 16
             anchors.verticalCenter: parent.verticalCenter
        }

        Label {
            id: pageTitle
            text: getChatUsername()
            font.pixelSize: 20

            anchors.centerIn: parent
        }
    }

    Image {
        id: backgroundImage
        source: "qrc:/images/chat_background.png"
        fillMode: Image.PreserveAspectCrop

        anchors.fill: parent
    }

        ListView {
            id: listView
            spacing: 8
            verticalLayoutDirection: ListView.BottomToTop

            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: messageField.top
            anchors.bottomMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8

            model: messagesTable

            delegate: MessageDelegate {}
        }

        MessageField {
            id: messageField

            onSendClicked: {
                root.sendButtonClicked(text);
                text = ""
            }

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }
}




