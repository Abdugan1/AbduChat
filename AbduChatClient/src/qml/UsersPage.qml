import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    signal userClicked(int userId);

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
                anchors.leftMargin: 16
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
        onCountChanged: {
            noResultsImage.playing = (count === 0)
        }

        model: usersTable;

        delegate: UsersDelegate { onUserClicked: { root.userClicked(userId) } }

        Item {
            id: noResults
            visible: listView.count === 0 && searchField.text !== ""
            anchors.top: parent.top
            anchors.topMargin: 150
            anchors.horizontalCenter: parent.horizontalCenter
            AnimatedImage {
                id: noResultsImage
                width: 200
                height: 200
                source: "qrc:/images/no_results.gif"
                anchors.horizontalCenter: parent.horizontalCenter
                speed: 1.5

                onFrameChanged: {
                    if (currentFrame === frameCount - 2)
                        playing = false
                }
            }
            Label {
                id: noResultsLabel
                text: qsTr("No results")
                anchors.top: noResultsImage.bottom
                anchors.topMargin: -20
                font.pointSize: 18
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
