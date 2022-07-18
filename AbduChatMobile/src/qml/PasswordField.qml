import QtQuick 2.0

ValidatedField {
    id: root

    echoMode: toggleVisibleButton.showPassword ? TextInput.Normal
                                               : TextInput.Password

    textField.rightPadding: 45

    Image {
        id: toggleVisibleButton

        property bool showPassword: false

        source: showPassword ? "qrc:/images/hide_password.png"
                             : "qrc:/images/show_password.png"

        sourceSize.height: 22

        anchors.right: parent.right
        anchors.rightMargin: 14
        anchors.verticalCenter: textField.verticalCenter

        MouseArea {
            anchors.fill: parent
            onClicked: { toggleVisibleButton.showPassword = !toggleVisibleButton.showPassword; }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
