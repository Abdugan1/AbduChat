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

    ValidatedField {
        id: usernameField
        width: 300
        height: 54
        anchors.top: authorizationLabel.bottom
        anchors.topMargin: 17
        placeholderText: qsTr("Username")
        anchors.horizontalCenter: parent.horizontalCenter
        iconSource: "../../resources/images/user.png"
        borderRadius: 40
        borderWidth: 2
    }

    Image {
        id: appLogo
        width: 200
        height: 200
        anchors.top: parent.top
        source: "../../resources/images/app_logo_256.png"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 61
        sourceSize.height: 256
        sourceSize.width: 256
        fillMode: Image.PreserveAspectFit
    }

    ValidatedField {
        id: passwordField
        width: 300
        height: 54
        anchors.top: usernameField.bottom
        placeholderText: qsTr("Password")
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        borderRadius: 40
        borderWidth: 2
        iconSource: "../../resources/images/padlock.png"
    }

    Label {
        id: authorizationLabel
        text: qsTr("LOGIN")
        anchors.top: appLogo.bottom
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 30
    }

    CustomButton {
        id: loginButton
        y: 528
        width: 300
        height: 50
        text: "LOGIN"
        enabled: false
        borderRadius: 50
        textColor: "#ffffff"
        backgroundColor: "#000000"
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
