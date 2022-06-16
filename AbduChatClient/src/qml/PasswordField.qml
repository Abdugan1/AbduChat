import QtQuick 2.0

ValidatedField {
    id: root
    width: 300
    height: 50
    state: "showPasswordState"

    rightPadding: 45

    states: [
        State {
            name: "showPasswordState"
            when: toggleVisiblePasswordImage.showPassword
            PropertyChanges {
                target: toggleVisiblePasswordImage
                source: "qrc:/images/hide_password.png"
            }
            PropertyChanges {
                target: root
                echoMode: TextInput.Normal
            }
        },
        State {
            name: "hidePasswordState"
            when: !toggleVisiblePasswordImage.showPassword
            PropertyChanges {
                target: toggleVisiblePasswordImage
                source: "qrc:/images/show_password.png"
            }
            PropertyChanges {
                target: root
                echoMode: TextInput.Password
            }
        }
    ]

    Image {
        id: toggleVisiblePasswordImage

        property bool showPassword: false

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        sourceSize.height: 22
        anchors.rightMargin: 14

        MouseArea {
            anchors.fill: parent
            onClicked: {
                toggleVisiblePasswordImage.showPassword = !toggleVisiblePasswordImage.showPassword;
            }
        }
    }
}
