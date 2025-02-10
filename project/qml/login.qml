import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 400
    height: 300

    Column {
        anchors.centerIn: parent
        spacing: 10

        TextField {
            id: usernameField
            placeholderText: "Enter Username"
            text: backend ? backend.username : "" // Ensure backend exists
            onTextChanged: if (backend)
                backend.username = text
        }

        TextField {
            id: passwordField
            placeholderText: "Enter Password"
            echoMode: TextInput.Password
            text: backend ? backend.password : "" // Ensure backend exists
            onTextChanged: if (backend)
                backend.password = text
        }

        Button {
            text: "Login"
            onClicked: if (backend)
                backend.login()
        }

        Text {
            id: statusText
            color: "red"
        }
    }

    Timer {
        id: delayTimer
        interval: 2000
        running: false
        repeat: false
        onTriggered: {
            console.log("2 seconds elapsed!");
            statusText.text = "";
        }
    }

    Connections {
        target: backend
        function onLoginSuccess() {
            statusText.text = "Login Successful!";
            statusText.color = "green";
            delayTimer.start();

            // Push employees.qml after delay
            delayTimer.onTriggered.connect(() => {
                stackView.push(Qt.resolvedUrl("employees.qml"));
            });
        }

        function onLoginFailed() {
            statusText.text = "Login Failed. Try Again!";
            statusText.color = "red";
        }
    }
}
