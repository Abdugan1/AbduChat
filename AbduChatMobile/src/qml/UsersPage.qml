import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    signal userClicked(int userId);

    implicitWidth: 440
    implicitHeight: 760

    header: ToolBar {
        height: searchField.height

        Item {
            id: header
            anchors.fill: parent

            BackButton {
                id: backButton

                anchors.left: parent.left
                anchors.leftMargin: 16
                anchors.verticalCenter: parent.verticalCenter
            }

            UserSearchField {
                id: searchField

                anchors.left: backButton.right
                anchors.leftMargin: 16
                anchors.right: parent.right
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: usersTable;

        onCountChanged: { noResultsImage.playing = (count === 0) }

        delegate: UsersDelegate { onUserClicked: { root.userClicked(userId) } }

        Item {
            id: noResults

            visible: listView.count === 0 && searchField.text !== ""

            anchors.top: parent.top
            anchors.topMargin: 150
            anchors.horizontalCenter: parent.horizontalCenter

            AnimatedImage {
                id: noResultsImage

                source: "qrc:/images/no_results.gif"
                speed: 1.5
                width: 200
                height: 200

                anchors.horizontalCenter: parent.horizontalCenter

                onFrameChanged: {
                    if (currentFrame === frameCount - 2)
                        playing = false
                }
            }
            Label {
                id: noResultsLabel
                text: qsTr("No results")
                font.pointSize: 18

                anchors.top: noResultsImage.bottom
                anchors.topMargin: -20
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
