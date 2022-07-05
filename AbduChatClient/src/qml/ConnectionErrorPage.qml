import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    signal reconnectButtonClicked()

    width: 440
    height: 760

    AnimatedImage {
        id: image
        anchors.top: parent.top
        source: "qrc:/images/no_connection.gif"
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: title
        text: qsTr("Whoops!")
        anchors.top: image.bottom
        font.bold: false
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
    }

    Label {
        id: reason
        width: 300
        text: qsTr("No internet connection or can't reach the server. Try again.")
        anchors.top: title.bottom
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.Wrap
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
    }

    CustomButton {
        id: customButton
        y: 572
        text: qsTr("TRY AGAIN")
        anchors.bottom: parent.bottom
        borderWidth: 0
        anchors.bottomMargin: 120
        borderRadius: 25
        anchors.horizontalCenter: parent.horizontalCenter
        textColor: "#ffffff"
        backgroundColor: "#000000"
        width: 300
        height: 50

        onClicked: {
            root.reconnectButtonClicked();
        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:4}
}
##^##*/
