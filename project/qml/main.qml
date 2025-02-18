import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 1820
    height: 1080

    StackView {
        id: stackView
        anchors.fill: parent
    }

    Component.onCompleted: {
        let loginComponent = Qt.createComponent("template.qml");
        if (loginComponent.status === Component.Ready)
            stackView.push(loginComponent.createObject(stackView));
        else
            console.log("Failed to load login.qml");
    }
}
