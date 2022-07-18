import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    signal reconnectButtonClicked()

    implicitWidth: 440
    implicitHeight: 760

    AnimatedImage {
        id: image
        source: "qrc:/images/no_connection.gif"

        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: title
        text: qsTr("Whoops!")
        font.bold: false
        font.pointSize: 24

        anchors.top: image.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: reason
        width: 300
        text: qsTr("No internet connection or can't reach the server. Try again.")
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignHCenter

        anchors.top: title.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    CustomButton {
        id: customButton
        text: qsTr("TRY AGAIN")
        onClicked: { root.reconnectButtonClicked(); }

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 120
        anchors.horizontalCenter: parent.horizontalCenter
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
