import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import AbduChatLib 1.0

Page {
    id: root

    property string inConversationWith
    property int inConversationWithId
    property alias messageField: messageField

    signal sendButtonClicked()

    header: ToolBar {
        Button {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            onClicked: { root.StackView.view.pop(); }
        }

        Label {
            id: pageTitle
            text: inConversationWith
            anchors.centerIn: parent
            font.pixelSize: 20
        }
    }

    MessagesTable {
        id: messagesTable
        objectName: "messagesTable"

        myId: getId()
        recipientId: root.inConversationWithId
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            verticalLayoutDirection: ListView.BottomToTop

            model: messagesTable

            delegate: Column {
                readonly property bool sentByMe: getId() === model.from_user_id

                anchors.right: sentByMe ? listView.contentItem.right : undefined
                spacing: 6

                RowLayout {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined

                    Image {
                        id: avatar
                        source: !sentByMe ? "qrc:/images/avatar.png" : ""
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }

                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24,
                                        listView.width - (!sentByMe ? avatar.width + messageRow.spacing : 0))
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "steelblue"

                        Label {
                            id: messageText
                            text: model.text
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }

                Label {
                    id: timestampText
                    text: model.sent_datetime
                    color: "lightgrey"
                    anchors.right: sentByMe ? parent.right : undefined
                }
            }
        }

        Pane {
            id: pane
            Layout.fillWidth: true

            RowLayout {
                width: parent.width
                spacing: 0

                TextField {
                    id: messageField
                    Layout.fillWidth: true
                }

                Button {
                    id: sendButton
                    text: qsTr("Send")

                    onClicked: { sendButtonClicked(); }
                }
            }
        }
    }
}
