import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import AbduChatLib 1.0

Page {
    id: root

    signal userClicked(string username, int id)

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
            topMargin: 48
            leftMargin: 48
            bottomMargin: 48
            rightMargin: 48

            model: contactsTable

            delegate: ItemDelegate {
                text: model.username
                font.pixelSize: 16
                width: listView.width - listView.leftMargin - listView.rightMargin
                leftPadding: avatar.implicitWidth + 16

                onClicked: { userClicked(model.username, model.id) }

                Image {
                    id: avatar
                    source: "qrc:/images/avatar.png"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    ContactsTable {
        id: contactsTable
        objectName: "contactsTable"
        myId: getId()
    }
}
