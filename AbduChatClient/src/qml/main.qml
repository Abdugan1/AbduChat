import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

import AbduChatClient 1.0

ApplicationWindow {
    id: window

    property string username: chatClient.username
    property int id: chatClient.id

    function getUsername() {return username}
    function getId() {return id}

    function rollBackToBegin() {stackView.pop(null);}

    width: 440
    height: 760
    visible: true

    Component.onCompleted: {
        chatClient.connectToHost();
    }

    ChatClient {
        id: chatClient
        objectName: "chatClient"

        onLoggedIn: {
            synchronizeAll();
            stackView.push(contactPage)
        }

        onLoginError: {
        }

        onConnected: {
            if (stackView.currentItem == connectionErrorPage)
                stackView.replace(connectionErrorPage, logInPage)
        }

        onErrorOccurred: {
            connectionErrorPage.reconnectIndicator.running = false
            if (stackView.currentItem != connectionErrorPage)
                stackView.replace(logInPage, connectionErrorPage)
            rollBackToBegin();
        }
    }

    LogInPage {
        id: logInPage

        onLoginButtonClicked: {
            chatClient.attempToLogIn(username, password);
        }

        onRegisterButtonClicked: {
            chatClient.attempToRegister(username, password);
        }
    }

    ContactPage {
        id: contactPage

        onUserClicked: {
            stackView.push(conversationPage, {inConversationWith: username, inConversationWithId: id})
        }
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
