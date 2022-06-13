import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root

    property string username: usernameField.text
    property string password: passwordField.text

    signal loginButtonClicked();
    signal registerButtonClicked();
    signal reconnectButtonClicked();

    function setReconnectButtionVisible(visible) {
        reconnectButton.visible = visible;
    }

    ColumnLayout {
        anchors.centerIn: parent

        Label {
            text: qsTr("Username")
        }

        TextField {
            id: usernameField
        }

        Label {
            text: qsTr("Password")
        }

        TextField {
            id: passwordField
            echoMode: TextField.Password
        }

        Button {
            id: logInButton
            Layout.fillWidth: true
            text: "Log In"

            onClicked: {
                loginButtonClicked();
            }
        }

        Button {
            id: registerButton
            Layout.fillWidth: true
            text: "Register"

            onClicked: {
                registerButtonClicked();
            }
        }

        Button {
            id: reconnectButton
            Layout.fillWidth: true
            text: "Reconnect"
            visible: false

            onClicked: {
                reconnectButtonClicked();
            }
        }
    }


}
