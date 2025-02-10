import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            text: "Home Page"
            font.pixelSize: 20
        }

        Button {
            text: "Back"
            onClicked: stackView.pop() // Go back to Login
        }
    }
}
