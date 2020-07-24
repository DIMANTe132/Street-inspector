import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow { id: root

    visible: true
    width: 390
    height: 430

    title: "Sign in"

    Text { id: element1
        width: 80
        height: 40

        text: qsTr("Вход")
        anchors.left: parent.left
        anchors.leftMargin: 155
        anchors.top: parent.top
        anchors.topMargin: 6
        font.family: "Arial"
        fontSizeMode: Text.FixedSize
        textFormat: Text.PlainText
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 32
    }

    Rectangle { id: rectangleofemail
        x: 39
        y: 122
        width: 306
        height: 189

        color: "#d0c8c8"
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0.4

        Label {
            id: description
            wrapMode: Text.WordWrap
            fontSizeMode: Text.FixedSize
            anchors.fill: parent
        }
    }

    Button { id: signup
        x: 104
        y: 342
        width: 25
        height: 25
        text: qsTr("+")
        anchors.horizontalCenterOffset: 112
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 15

        onClicked:
        {
            root.visible = false
            var component = Qt.createComponent("Child.qml")
            var window = component.createObject(root)
            window.show()
        }
    }

    Button {
        id: button1
        x: 7
        y: 397
        width: 85
        height: 20
        text: qsTr("Назад")
    }

    Label {
        id: supp
        x: 254
        y: 348
    }

    Label {
        id: fio
        x: 66
        y: 89
        font.pointSize: 12
    }
}



/*##^##
Designer {
    D{i:1;anchors_height:40;anchors_width:120;anchors_x:34;anchors_y:9}D{i:2;anchors_height:15;anchors_width:270;anchors_x:34;anchors_y:52}
D{i:4;anchors_height:38;anchors_width:312;anchors_x:0;anchors_y:0}D{i:3;anchors_height:38;anchors_width:312;anchors_x:39;anchors_y:149}
D{i:6;anchors_height:35;anchors_width:312;anchors_x:0;anchors_y:0}D{i:5;anchors_height:35;anchors_x:39;anchors_y:235}
}
##^##*/
