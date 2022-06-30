import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    signal chatClicked(string chatUsername)

    width: 440
    height: 760

    header: ToolBar {
        height: 43
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        Item {
            id: header
            anchors.fill: parent
            Label {
                id: title
                text: qsTr("AbduChat")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 32
                font.pointSize: 18
            }
            Image {
                id: searchButton
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/images/search_24.png"
                anchors.rightMargin: 16
                anchors.right: parent.right
                MouseArea {
                    anchors.fill: parent
                    onClicked: { stackView.push(usersPage) }
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: getChatsViewTable()

        delegate: ChatDelegate {}
    }
}
