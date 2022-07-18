import QtQuick 2.15
import QtQuick.Controls 2.15

import "qrc:/js/validation.js" as Validation

Page {
    id: root

    readonly property int fieldSpacing: 0

    implicitWidth: 440
    implicitHeight: 760

    Label {
        id: signUpLabel
        text: qsTr("Sign Up")
        font.pointSize: 24

        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.left: usernameField.left
        anchors.leftMargin: 0
    }

    ValidatedField {
        id: usernameField
        iconSource: "qrc:/images/user.png"
        placeholderText: qsTr("Username")

        validator: RegularExpressionValidator {
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

        anchors.top: signUpLabel.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    PasswordField {
        id: passwordField
        iconSource: "qrc:/images/padlock.png"
        placeholderText: qsTr("Password")

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
    }

    PasswordField {
        id: confirmPasswordField
        iconSource: "qrc:/images/padlock.png"
        placeholderText: qsTr("Confirm password")

        errorMessage: qsTr("Passwords do not match")

        textField.onActiveFocusChanged: {
            hasError = passwordField.textField.text != confirmPasswordField.textField.text
        }

        anchors.top: passwordField.bottom
        anchors.topMargin: root.fieldSpacing
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ValidatedField {
        id: firstNameField
        iconSource: "qrc:/images/user.png"
        placeholderText: qsTr("First name")

        validator: RegularExpressionValidator {
            regularExpression: Validation.NameRegex
        }
        errorMessage: qsTr("Invalid name")

        textField.onActiveFocusChanged: {
            hasError = !textField.activeFocus && !textField.acceptableInput
        }

        anchors.top: confirmPasswordField.bottom
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
    }

    ValidatedField {
        id: lastNameField
        borderWidth: root.fieldBorderWidth
        iconSource: "qrc:/images/user.png"
        placeholderText: qsTr("Last name")

        validator: RegularExpressionValidator {
            regularExpression: Validation.NameRegex
        }
        errorMessage: qsTr("Invalid name")

        textField.onActiveFocusChanged: {
            hasError = !textField.activeFocus && !textField.acceptableInput
        }

        anchors.top: firstNameField.bottom
        anchors.topMargin: root.fieldSpacing
        anchors.horizontalCenter: parent.horizontalCenter
    }

    CustomButton {
        id: signUpButton
        text: qsTr("SIGN UP")

        anchors.top: lastNameField.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: goToLoginPageLabel
        text: qsTr("Already have an account? <a href=\":\">Login</a>")
        onLinkActivated: { stackView.replace(stackView.currentItem, logInPage) }

        anchors.top: signUpButton.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
    }
}





/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
