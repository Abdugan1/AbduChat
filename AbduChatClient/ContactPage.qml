import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import AbduChatLib 1.0

Page {
    id: root

    signal userClicked(string username)

    header: ToolBar {
        Label {
            text: qsTr("Contacts")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: contactsTable

            delegate: ItemDelegate {
                text: model.username
                font.pixelSize: 16

                onClicked: {
                    userClicked(model.username)
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: usernameField
                Layout.fillWidth: true
            }

            Button {
                id: insertButton

                onClicked: {
                    contactsTable.insertUsername(usernameField.text);
                    usernameField.text = ""
                }
            }
        }
    }

    ContactsTable {
        id: contactsTable
        objectName: "contactsTable"
    }
}
