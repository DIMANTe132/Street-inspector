import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow { id: root

    visible: true
    width: 390
    height: 430

    title: "Registration"

    Text { id: element1

        x: 34
        y: 9
        width: 120
        height: 40
        text: qsTr("Sign Up")
        font.family: "Arial"
        fontSizeMode: Text.FixedSize
        textFormat: Text.PlainText
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 32
    }

    Text { id: element2

        x: 34
        y: 52
        width: 270
        height: 15
        color: "#000000"
        text: qsTr("Please fill in this form to create an account!")
        opacity: 0.3
        font.pixelSize: 14
    }

    Rectangle { id: rectangleofname

        x: 34
        y: 103
        width: 150
        height: 37
        color: "#d0c8c8"
        opacity: 0.4

        TextField {id: first

            x: 0
            y: 0
            width: 150
            height: 37
            placeholderText: qsTr("First Name")
            font.family: "Arial"
            font.pointSize: 12
            opacity: 1
        }
    }

    Rectangle { id: rectangleoflastname

        x: 197
        y: 103
        width: 150
        height: 37
        color: "#d0c8c8"
        opacity: 0.4

        TextField { id: last

            x: -1
            y: 0
            width: 150
            height: 37
            placeholderText: qsTr("Last Name")
            font.family: "Arial"
            font.pointSize: 12
            opacity: 1
        }
    }

    ComboBox { id: country

        x: 34
        y: 159
        width: 312
        height: 37
        editable: false
        font.pointSize: 12
        opacity: 0.3

        model: ListModel
        {
            ListElement { text: "Select your country"}
            ListElement { text: "Russia" }
            ListElement { text: "United Kingdom" }
            ListElement { text: "USA" }
        }
    }

    Rectangle { id: rectangleofemail

        x: 34
        y: 211
        width: 312
        height: 38
        color: "#d0c8c8"

        TextField { id: email

            x: 0
            y: 0
            width: 312
            height: 38
            placeholderText: qsTr("Email")
            font.family: "Arial"
            font.pointSize: 12
            opacity: 1
        }
        opacity: 0.4
    }

    Rectangle { id: rectangleofpassword

        x: 34
        y: 271
        width: 312
        height: 35
        color: "#d0c8c8"

        TextField { id: password

            x: 0
            y: 0
            width: 312
            height: 35
            placeholderText: qsTr("Password")
            font.family: "Arial"
            echoMode: TextInput.Password
            passwordCharacter: "*"
            font.pointSize: 12
        }
        opacity: 0.4
    }

    CheckBox { id: checkBox

        x: 34
        y: 324
        width: 189
        height: 40
        text: qsTr("I accept the Terms of Use")
        display: AbstractButton.IconOnly
        font.pointSize: 9
        tristate: false
        checkState: Qt.Unchecked
        checked: false
        opacity: 0.4
    }

    Button { id: signup
        x: 34
        y: 370
        width: 130
        height: 37
        text: qsTr("Sign Up")

        enabled:
        {
            if (first.text == "" || email.text == "" || password.text == "" ||
                country.currentIndex ==  0 || checkBox.checked == false)
                false
            else
                true
        }
        onClicked:
        {
            root.visible = false
            var component = Qt.createComponent("Child.qml")
            var window = component.createObject(root)
            window.show()
        }
    }

    function checklistenter(checklist)
    {
        if(first.text == "")
            checklist += "First name is not entered\n"
        if(country.currentIndex == 0)
            checklist += "Country is not entered\n"
        if(email.text == "")
            checklist += "Mail is not entered\n"
        if(password.text == "")
            checklist += "Password is not entered\n"
        if(checkBox.checked == false)
            checklist += "Terms of use not accepted\n"
        return checklist
    }

    Button { id: check
        x: 250
        y: 380
        width: 20
        height: 20
        text: qsTr("?")
        property string checklist: ""
        ToolTip.visible: hovered
        ToolTip.text:
        {
            if (checklistenter(checklist) === "")
                "Everything is ready"
            else
                checklistenter(checklist)
        }
    }
}


