import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    property int textInputWidth: 350
    property int textInputHeight: 54

    property color backgroundColor: "white"
    property color borderColor: "black"
    property int borderWidth: 1
    property real borderRadius: 10

    property alias textField: textInput
    property alias text: textInput.text
    property alias iconSource: icon.source
    property alias iconSourceSize: icon.sourceSize
    property alias placeholderText: textInput.placeholderText
    property alias validator: textInput.validator
    property alias echoMode: textInput.echoMode

    property bool isInputCorrect: textInput.acceptableInput && !hasError && textInput.text.length > 0
    property bool hasError: false
    property string errorMessage: qsTr("Error")
    property color errorColor: "red"

    QtObject {
        id: internal
        property bool displayError: root.hasError && !textInput.activeFocus
    }

    width: textInput.width
    height: textInput.height + errorText.implicitHeight

    states: [
        State {
            when: internal.displayError
            PropertyChanges {
                target: root
                borderColor: root.errorColor
            }
        }
    ]

    TextField {
        id: textInput

        width: root.textInputWidth
        height: root.textInputHeight

        leftPadding: 42
        placeholderTextColor: "grey"
        selectByMouse: true

        background: Rectangle {
            id: backgroundRectangle

            color: root.backgroundColor
            border.color: root.borderColor
            border.width: root.borderWidth
            radius: root.borderRadius

            Image {
                id: icon

                source: root.iconSource
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                sourceSize.height: 20
            }
        }
    }

    Label {
        id: errorText
        text: root.errorMessage
        color: root.errorColor
        visible: internal.displayError

        anchors.top: textInput.bottom
    }
}


