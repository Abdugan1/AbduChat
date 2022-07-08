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

    width: 440
    height: 760
    visible: true

    header: ToolBar {
        height: 43
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        BackButton {
             anchors.left: parent.left
             anchors.verticalCenter: parent.verticalCenter
             anchors.leftMargin: 16
        }

        Label {
            id: pageTitle
            text: getChatUsername()
            anchors.centerIn: parent
            font.pixelSize: 20
        }
    }

        ListView {
            id: listView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: messageField.top
            anchors.rightMargin: 8
            anchors.leftMargin: 8
            anchors.bottomMargin: 8
            anchors.topMargin: 8
            spacing: 8
            verticalLayoutDirection: ListView.BottomToTop

            model: messagesTable
//            model: ListModel {
//                ListElement {
//                    text: "Hale epta"
//                }
//                ListElement {
//                    text: "Hale epta #2 Loremdsakl"
//                }
//            }

            delegate: MessageDelegate {

            }
        }

        MessageField {
            id: messageField
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            onSendClicked: {
                sendButtonClicked(text);
                text = ""
            }
        }
}




