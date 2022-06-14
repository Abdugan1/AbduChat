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

    function rollBackToLoginPage() {stackView.pop(null);}

    width: 440
    height: 760
    visible: true

    ChatClient {
        id: chatClient
        objectName: "chatClient"

        Component.onCompleted: {
            connectToHost();
        }

        onLoggedIn: {
            synchronizeAll();
            stackView.push(contactPage)
        }

        onLoginError: {
        }

        onErrorOccurred: {
            rollBackToLoginPage();
            logInPage.setReconnectButtionVisible(true);
            messageDialog.text = errorString;
            messageDialog.open();
        }
    }

    MessageDialog {
        id: messageDialog
        title: "Error"
    }

    LogInPage {
        id: logInPage

        onLoginButtonClicked: {
            chatClient.attempToLogIn(username, password);
        }

        onRegisterButtonClicked: {
            chatClient.attempToRegister(username, password);
        }

        onReconnectButtonClicked: {
            chatClient.connectToHost();
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

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: logInPage
    }
}
