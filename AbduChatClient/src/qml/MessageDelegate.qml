import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root

    readonly property int margin: 100

    property bool sentByMe: getMyUser().id == model.from_user_id

    function getContentWidth() {
        return textLabel.implicitWidth + textLabel.anchors.leftMargin + textLabel.anchors.rightMargin
                + dateText.implicitWidth + dateText.anchors.rightMargin
    }

    function getMaxWidht() { return listView.width - margin; }

    function getContentHeight() {
        console.log("\nmy_id: " + getMyUser().id)
        console.log("from_user: " + model.from_user_id)
        return textLabel.implicitHeight  + textLabel.anchors.margins * 2;
    }

    width: Math.min(getContentWidth(), getMaxWidht())
    height: getContentHeight()
//    width: 300
//    height: 50
    color: "#202123"
    radius: 20

    Label {
        id: textLabel
        color: "#fafafb"
        font.pointSize: 14
        text: model.text
        anchors.fill: parent
        anchors.margins: 14
        wrapMode: Text.Wrap
    }

    Text {
        id: dateText
        color: "#7e7f81"
        text: "9:41"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        font.pointSize: 12
        anchors.bottomMargin: 4
        anchors.rightMargin: 20
    }
    states: [
        State {
            name: "sentByMe"
            when: root.sentByMe

            PropertyChanges {
                target: dateText
                color: "#8CCAF5"
            }

            PropertyChanges {
                target: root
                color: "#3879B3"
                anchors.right: parent.right
            }

            PropertyChanges {
                target: textLabel
                color: "#fafafb"
            }
        }
    ]
}






