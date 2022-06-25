import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root

    property alias reconnectIndicator: reconnectIndicator

    signal reconnectButtonClicked()

    width: 440
    height: 760

    ColumnLayout {
        anchors.fill: parent

        Item {
            // spacer item
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Image {
            id: image
            Layout.alignment: Qt.AlignHCenter

            source: "qrc:/images/connection_error.png"
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("<b>Connection Error</b>")
        }

        Label {
            Layout.alignment: Qt.AlignHCenter
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("No Internet connection or\ncan't reach the server")
        }

        Item {
            // spacer item
            Layout.fillWidth: true
            Layout.fillHeight: true

            BusyIndicator {
                id: reconnectIndicator

                anchors.centerIn: parent
                running: false
            }
        }

        Button {
            id: reconnectButton
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("TRY AGAIN")

            onClicked: {
                reconnectIndicator.running = true
                reconnectButtonClicked()
            }
        }

        Item {
            // spacer item
            Layout.fillWidth: true
            height: 100
        }
    }
}
