import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "qrc:/js/validation.js" as Validation

Page {
    id: root

    property string username: usernameField.text
    property string password: passwordField.text

    readonly property int fieldSpacing: 0

    signal loginButtonClicked();

    implicitWidth: 440
    implicitHeight: 760

    function setReconnectButtionVisible(visible) {
        reconnectButton.visible = visible;
    }

    Image {
        id: appLogo
        width: 200
        height: 200
        source: "qrc:/images/app_logo_256.png"
        fillMode: Image.PreserveAspectFit

        anchors.top: parent.top
        anchors.topMargin: 61
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: authorizationLabel
        text: qsTr("LOGIN")
        font.pointSize: 24

        anchors.top: appLogo.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ValidatedField {
        id: usernameField
        iconSource: "qrc:/images/user.png"
        placeholderText: qsTr("Username")

        errorMessage: qsTr("Invalid username")
        validator: RegularExpressionValidator {
            // length: 4-20
            regularExpression: Validation.UsernameRegex
        }

        textField.onActiveFocusChanged: {
            hasError = !textField.activeFocus && !textField.acceptableInput

            if (hasError) {
                var textLength = textField.text.length;
                if (textLength == 0) {
                    errorMessage = qsTr("Enter username");
                } else if (textLength < 4) {
                    errorMessage = qsTr("Username must contain at least 4 characters");
                } else {
                    errorMessage = qsTr("Invalid username");
                }
            }
        }


        anchors.top: authorizationLabel.bottom
        anchors.topMargin: 17
        anchors.horizontalCenter: parent.horizontalCenter
    }

    PasswordField {
        id: passwordField
        iconSource: "qrc:/images/padlock.png"
        placeholderText: qsTr("Password")

        errorMessage: qsTr("Invalid password")
        validator: RegularExpressionValidator {
            regularExpression: Validation.PasswordRegex
        }

        textField.onActiveFocusChanged: {
            hasError = !textField.activeFocus && !textField.acceptableInput
            if (!hasError)
                return;

            var text = textField.text;
            var textLength = textField.text.length;
            if (textLength == 0) {
                errorMessage = qsTr("Enter password");
            } /*else if (textLength < 8) {
                errorMessage = qsTr("Password must contain at least 8 characters");
            }*/ else {
                errorMessage = qsTr("Invalid password");
            }
        }

        anchors.top: usernameField.bottom
        anchors.topMargin: root.fieldSpacing
        anchors.horizontalCenter: parent.horizontalCenter

        Popup {
            id: passwordPopup

            contentItem: Text {
                text: qsTr("8 characters")
            }
        }
    }

    CustomButton {
        id: loginButton
        width: root.fieldWidth
        height: root.fieldHeight
        borderRadius: root.fieldRadius
        borderWidth: 0
        text: qsTr("LOGIN")

        onClicked: { root.loginButtonClicked() }

        anchors.top: passwordField.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: label
        text: qsTr("Don't have an account yet? <a href=\":\">Sign up</a>")
        onLinkActivated: { stackView.replace(stackView.currentItem, signUpPage) }

        anchors.top: loginButton.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
