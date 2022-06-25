import QtQuick 2.15
import QtQuick.Controls 2.15

//import AbduChatLib 1.0

Page {
    id: root

    property string inConversationWith
    property int inConversationWithId

    signal sendButtonClicked()

    width: 440
    height: 760
    visible: true

    header: ToolBar {
        height: 43
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        BackButton {
             anchors.left: parent.left
             anchors.verticalCenter: parent.verticalCenter
             anchors.leftMargin: 16
        }

        Label {
            id: pageTitle
            text: "inConversationWith"
            anchors.centerIn: parent
            font.pixelSize: 20
        }
    }

//    MessagesTable {
//        id: messagesTable
//        objectName: "messagesTable"

//        myId: getId()
//        recipientId: root.inConversationWithId
//    }

//        ListView {
//            id: listView
//            anchors.left: parent.left
//            anchors.right: parent.right
//            anchors.top: parent.top
//            anchors.bottom: messageField.top
//            anchors.rightMargin: 0
//            anchors.leftMargin: 0
//            anchors.bottomMargin: 0
//            anchors.topMargin: 0
//            verticalLayoutDirection: ListView.BottomToTop

//            model: messagesTable
//        }

        MessageField {
            id: messageField
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            onSendClicked: {
                console.log("Send clicked");
            }
        }
}




