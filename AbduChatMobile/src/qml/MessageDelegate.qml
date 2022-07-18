import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root

    readonly property int margin: 100

    property bool sentByMe: chatClient.user.id === model.from_user_id

    function getContentWidth() {
        return textLabel.implicitWidth + textLabel.anchors.leftMargin + textLabel.anchors.rightMargin
                + dateText.implicitWidth + dateText.anchors.rightMargin
    }

    function getMaxWidht() { return listView.width - margin; }

    function getContentHeight() { return textLabel.implicitHeight  + textLabel.anchors.margins * 2; }

    function getDate(dateString) {
        var date = Date.fromLocaleString(Qt.locale(), dateString, dateFormat);
        return date.toLocaleString(Qt.locale(), "hh:mm");
    }

    implicitWidth: 440
    implicitHeight: 760
    width: Math.min(getContentWidth(), getMaxWidht())
    height: getContentHeight()
    color: "#202123"
    radius: 20

    Label {
        id: textLabel
        text: model.text
        color: "#fafafb"
        font.pointSize: 14
        wrapMode: Text.Wrap

        anchors.fill: parent
        anchors.margins: 15
    }

    Text {
        id: dateText
        text: getDate(model.date)
        color: "#7e7f81"
        font.pointSize: 12

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.right: parent.right
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








