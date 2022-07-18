import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    signal chatClicked()

    implicitWidth: 440
    implicitHeight: 760

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
                font.pointSize: 18

                anchors.left: parent.left
                anchors.leftMargin: 32
                anchors.verticalCenter: parent.verticalCenter
            }

            Image {
                id: searchButton
                source: "qrc:/images/search_24.png"

                anchors.right: parent.right
                anchors.rightMargin: 16
                anchors.verticalCenter: parent.verticalCenter

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

        model: chatsViewTable

        delegate: ChatDelegate {
            onClicked: {
                database.setCurrentChat(chatId);
                root.chatClicked()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
