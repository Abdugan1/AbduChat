import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: root

    implicitHeight: 43
    implicitWidth: 300
    selectByMouse: true
    placeholderText: qsTr("Search")
    font.pointSize: 14

    rightPadding: clearButton.width + 2 * clearButton.anchors.rightMargin

    background: Rectangle{ color: "#00ffffff"}

    onTextChanged: usersTable.filterValue = root.text.trim()

    Image {
        id: clearButton
        source: "qrc:/images/x_16.png"
        visible: root.text != ""

        anchors.right: parent.right
        anchors.rightMargin: 16
        anchors.verticalCenter: parent.verticalCenter

        MouseArea {
            anchors.fill: parent
            onClicked: root.text = ""
        }
    }
}
