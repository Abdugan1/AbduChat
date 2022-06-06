import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

import AbduChatClient 1.0

ApplicationWindow {
    id: window
    width: 440
    height: 760
    visible: true

    ChatClient {
        id: chatClient

        Component.onCompleted: {
            connectToHost();
        }

        onErrorOccurred: {
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
            stackView.push(conversationPage, {inConversationWith: username})
        }
    }

    ConversationPage {
        id: conversationPage
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: logInPage
    }
}
