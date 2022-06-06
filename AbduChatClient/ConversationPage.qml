import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import AbduChatLib 1.0

Page {
    id: root

    property string inConversationWith

    header: ToolBar {
        Button {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
                root.StackView.view.pop();
            }
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
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: messagesTable
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 0

            TextField {
                id: messageField
                Layout.fillWidth: true
            }

            Button {
                id: sendButton
                text: qsTr("Send")
            }
        }
    }
}
