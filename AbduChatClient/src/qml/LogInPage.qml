import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root

    property string username: usernameField.text
    property string password: passwordField.text

    signal loginButtonClicked();
    signal registerButtonClicked();
    width: 440
    height: 760

    function setReconnectButtionVisible(visible) {
        reconnectButton.visible = visible;
    }

    Image {
        id: appLogo
        width: 200
        height: 200
        anchors.top: parent.top
        source: "qrc:/images/app_logo_256.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 61
        sourceSize.height: 256
        sourceSize.width: 256
        fillMode: Image.PreserveAspectFit
    }

    Label {
        id: authorizationLabel
        text: qsTr("LOGIN")
        anchors.top: appLogo.bottom
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 30
    }

    ValidatedField {
        id: usernameField
        width: 300
        height: 54
        anchors.top: authorizationLabel.bottom
        anchors.topMargin: 17
        placeholderText: qsTr("Username")
        anchors.horizontalCenter: parent.horizontalCenter
        iconSource: "qrc:/images/user.png"
        borderRadius: 40
        borderWidth: 2
    }

    PasswordField {
        id: passwordField
        x: 70
        height: 54
        anchors.top: usernameField.bottom
        state: "showPasswordState"
        anchors.topMargin: 10
        placeholderText: "Password"
        iconSource: "qrc:/images/padlock.png"
        borderWidth: 2
        borderRadius: 40
    }

    CustomButton {
        id: loginButton
        y: 528
        width: 300
        height: 50
        text: "LOGIN"
        borderWidth: 0
        state: ""
        borderRadius: 50
        textColor: "#ffffff"
        backgroundColor: "#000000"
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: { root.loginButtonClicked() }
    }

    Label {
        id: label
        y: 676
        text: qsTr("Don't have an account yet? <a href=\":\">Sign up</a>")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        onLinkActivated: {
            console.log("Go to sign up page")
        }
    }
}
