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
            text: Login ? Login.username : "" // Ensure Login exists
            onTextChanged: if (Login)
                Login.username = text
        }

        TextField {
            id: passwordField
            placeholderText: "Enter Password"
            echoMode: TextInput.Password
            text: Login ? Login.password : "" // Ensure Login exists
            onTextChanged: if (Login)
                Login.password = text
        }

        Button {
            text: "Login"
            onClicked: if (Login)
                Login.login()
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
        target: Login
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
