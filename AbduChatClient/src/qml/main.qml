import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: window

    readonly property string dateFormat: "yyyy-MM-ddTHH:mm:ss"

    function rollBackToBegin() { stackView.pop(null); }

    width: 440
    height: 760
    visible: true

    Component.onCompleted: { chatClient.connectToHost(); }

    Connections {
        target: chatClient

        function onConnected() {
            if (stackView.currentItem == connectionErrorPage)
                stackView.replace(connectionErrorPage, logInPage);
        }

        function onErrorOccurred() {
            if (stackView.currentItem != connectionErrorPage)
                stackView.replace(logInPage, connectionErrorPage)
            rollBackToBegin();
        }

        function onLoggedIn() {
            chatClient.synchronizeAll()
            stackView.push(chatsPage)
        }
    }

    LogInPage {
        id: logInPage

        onLoginButtonClicked: { chatClient.attempToLogIn(username, password); }

        onRegisterButtonClicked: { chatClient.attempToRegister(username, password); }
    }

    ChatsPage {
        id: chatsPage

        onChatClicked: { stackView.push(conversationPage) }
    }

    UsersPage {
        id: usersPage

        onUserClicked: {
            if (!chatsTable.hasChat(chatClient.user.id, userId)) {
                chatClient.requestCreateChat(userId);
            } else {
                database.setCurrentChat(chatClient.user.id, userId);
                stackView.replace(stackView.currentItem, conversationPage);
            }
        }
    }

    ConversationPage {
        id: conversationPage

        onSendButtonClicked: { chatClient.sendMessage(messagesTable.currentChat, messageText); }
    }

    ConnectionErrorPage {
        id: connectionErrorPage

        onReconnectButtonClicked: { chatClient.connectToHost() }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: logInPage
    }
}
