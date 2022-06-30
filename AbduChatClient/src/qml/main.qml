import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: window

    function rollBackToBegin() { stackView.pop(null); }

    function getChatClient() { return chatClient; }
    function getMyUser() { return chatClient.user; }
    function getCurrentChat() { return messagesTable.currentChat; }
    function setCurrentChat(newChat) {
        console.log("setCurrentChat");
        console.log("chat.id: " + newChat.chatId)
        console.log("chat.user1Id: " + newChat.user1Id)
        console.log("chat.user2Id: " + newChat.user2Id)
        messagesTable.setCurrentChat(newChat);
        console.log("chat.id: " + newChat.chatId)
        console.log("chat.user1Id: " + newChat.user1Id)
        console.log("chat.user2Id: " + newChat.user2Id)
    }

    function getUsersTable()     { return usersTable; }
    function getChatsViewTable() { return chatsViewTable; }
    function getMessagesTable()  { return messagesTable; }

    width: 440
    height: 760
    visible: true

    Component.onCompleted: {
        chatClient.connectToHost();
    }

    Connections {
        target: chatClient

        function onErrorOccurred() {
            connectionErrorPage.reconnectIndicator.running = false
            if (stackView.currentItem != connectionErrorPage)
                stackView.replace(logInPage, connectionErrorPage)
            rollBackToBegin();
        }

        function onLoggedIn() {
            console.log("my id: " + chatClient.user.id);
            console.log("my username: " + chatClient.user.username);
            console.log("my lastname: " + chatClient.user.lastName);
            chatClient.synchronizeAll()
            stackView.push(chatsPage)
        }
    }

//    ChatClient {
//        id: chatClient
//        objectName: "chatClient"

//        onLoggedIn: {
//            synchronizeAll();
//            stackView.push(contactPage)
//        }

//        onLoginError: {
//        }

//        onConnected: {
//            if (stackView.currentItem == connectionErrorPage)
//                stackView.replace(connectionErrorPage, logInPage)
//        }

//        onErrorOccurred: {
//            connectionErrorPage.reconnectIndicator.running = false
//            if (stackView.currentItem != connectionErrorPage)
//                stackView.replace(logInPage, connectionErrorPage)
//            rollBackToBegin();
//        }
//    }

    LogInPage {
        id: logInPage

        onLoginButtonClicked: {
            chatClient.attempToLogIn(username, password);
        }

        onRegisterButtonClicked: {
            chatClient.attempToRegister(username, password);
        }
    }

    ChatsPage {
        id: chatsPage

        onChatClicked: {
            stackView.push(conversationPage, {pageTitleText: chatUsername})
        }
    }

    UsersPage {
        id: usersPage
    }

    ConversationPage {
        id: conversationPage

        onSendButtonClicked: {
            console.log("send button clicked");
            chatClient.sendMessage(getCurrentChat(), messageText);
        }
    }

    ConnectionErrorPage {
        id: connectionErrorPage

        onReconnectButtonClicked: chatClient.connectToHost()
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: logInPage
    }
}
