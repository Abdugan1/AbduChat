import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    width: 440
    height: 760

    header: ToolBar {
        height: searchField.height
        Item {
            id: header
            anchors.fill: parent
            BackButton {
                id: backButton
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 16
            }
            UserSearchField {
                id: searchField
                anchors.left: backButton.right
                anchors.right: parent.right
                anchors.rightMargin: 16
                anchors.leftMargin: 32
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

//        model: ListModel {
//            ListElement {
//                username: "Abdugan1"
//            }
//            ListElement {
//                username: "nnegmetov"
//            }
//        }
        model: getUsersTable();

        delegate: UsersDelegate {
            onUserClicked: {
                getChatClient().requestCreateChat(id);
            }
        }
    }
}


