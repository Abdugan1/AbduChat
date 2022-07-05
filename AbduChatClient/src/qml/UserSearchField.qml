import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: root
    font.pointSize: 14

    placeholderText: qsTr("Search")
    selectByMouse: true

    implicitHeight: 43
    implicitWidth: 300
    rightPadding: clearButton.width + 2 * clearButton.anchors.rightMargin

    background: Rectangle{ color: "#00ffffff"}

    onTextChanged: usersTable.filterValue = root.text.trim()

    Image {
        id: clearButton
        visible: root.text != ""
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        source: "qrc:/images/x_16.png"
        anchors.rightMargin: 16

        MouseArea {
            anchors.fill: parent
            onClicked: root.text = ""
        }
    }
}
