import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: window

    function rollBackToBegin() { stackView.pop(null); }
    function getChatClient() { return chatClient; }
    function getMyUserId()   { return chatClient.myUserId; }
    function getUsersTable() { return usersTable; }

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

        onUserClicked: {
            stackView.push(conversationPage, {inConversationWith: username, inConversationWithId: id})
        }
    }

    UsersPage {
        id: usersPage
    }

    ConversationPage {
        id: conversationPage

        onSendButtonClicked: {
            chatClient.sendMessage(inConversationWithId, messageField.text);
            messageField.clear();
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
