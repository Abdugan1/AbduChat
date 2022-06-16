import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import AbduChatLib 1.0

Page {
    id: root

    signal userClicked(string username, int id)
    width: 440
    height: 760

    header: ToolBar {
        id: header
        bottomPadding: 12
        topPadding: 12
        Label {
            text: qsTr("AbduChat")
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            font.pixelSize: 20
            anchors.leftMargin: 42
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: contactsTable

        delegate: ChatDelegate {}
    }

    ContactsTable {
        id: contactsTable
        objectName: "contactsTable"
        myId: getId()
    }
}
