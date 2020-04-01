import QtQuick 2.0


Rectangle {
    property color btnColor: "#000"
    property color btnColorHover: btnColor
    property color btnTextColor: "#FFF"
    property color btnTextColorHover: btnTextColor
    property var fontSize: 35
    property bool isIcon
    property var onClick
    property alias text: btnText.text

    id: button
    color: mouseArea.containsMouse ? btnColorHover : btnColor
    implicitHeight: 100
    implicitWidth: 100

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            if (onClick !== undefined)
                onClick();
        }
    }

    Text {
        id: btnText
        anchors.centerIn: parent
        color: mouseArea.containsMouse ? btnTextColorHover : btnTextColor
        font.family: isIcon ? "Font Awesome 5 Solid" : "Consolas"
        font.pixelSize: fontSize
    }
}


