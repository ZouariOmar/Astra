/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import "../QtDS/UntitledProject"
import "../QtDS/UntitledProject/UntitledProjectContent"
import "../QtDS/UntitledProject/UntitledProject"
import "file:///home/zouari_omar/Qt/Tools/QtDesignStudio/effect_bundle"
import "file:///home/zouari_omar/Qt/Tools/QtDesignStudio/effect_bundle/designer"
import "file:///home/zouari_omar/Qt/Tools/QtDesignStudio/qt6_design_studio_reduced_version/qml/QtQuick/Studio/Components"
import "file:///home/zouari_omar/Qt/Tools/QtDesignStudio/qt6_design_studio_reduced_version/qml/QtQuick/Studio/DesignEffects"

Rectangle {
    width: 1920
    height: 1080
    radius: 5
    border.color: "black"
    border.width: 1

    // Property for hover animation
    property color hoverColor: "white"

    Behavior on hoverColor {
        ColorAnimation {
            duration: 300 // Smooth transition
        }
    }

    AnimatedImage {
        id: animatedImage
        anchors.fill: parent
        source: "../assets/login imgs/loginBkg.jpeg"

        Rectangle {
            id: rectangle
            x: 374
            y: 190
            width: 1172
            height: 700
            radius: 10
            border.width: 0
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#9f372a"
                }

                GradientStop {
                    position: 1
                    color: "#c7134f85"
                }
                orientation: Gradient.Vertical
            }

            GroupItem {
                id: usernameGrp
                x: 735
                y: 312

                TextInput {
                    id: txtUsernameIn
                    x: 0
                    y: 0
                    width: 338
                    height: 43
                    opacity: 1
                    color: "#3e000000"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    z: 1
                    mouseSelectionMode: TextInput.SelectCharacters
                    leftPadding: 35
                    font.weight: Font.Normal
                    echoMode: TextInput.Normal

                    text: "Username"
                    onTextChanged: if (Login)
                        Login.username = text
                }

                Rectangle {
                    id: rectangle4
                    x: 0
                    y: 1
                    width: 338
                    height: 42
                    opacity: 1
                    color: "#ffffff"
                    radius: 10
                    border.width: 0
                    z: 0
                    rotation: 0
                }

                Image {
                    id: image1
                    x: 2
                    y: 8
                    width: 28
                    height: 28
                    source: "../assets/login imgs/user.png"
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    id: mouseArea2
                    x: 0
                    y: 1
                    width: 338
                    height: 43
                    z: 1
                    cursorShape: Qt.IBeamCursor
                    hoverEnabled: true

                    onClicked: {
                        rectangle4.border.color = "RoyalBlue";
                        rectangle4.border.width = 2;
                        mouseArea2.z = 0;
                        txtUsernameIn.forceActiveFocus();

                        rectangle3.border.color = "#ffffff";
                        rectangle3.border.width = 0;
                        mouseArea3.z = 1;
                    }
                }
            }

            Image {
                id: image
                x: 854
                y: 141
                width: 100
                height: 100
                source: "../../doc/imgs/logo.png"
                activeFocusOnTab: false
                focus: false
                antialiasing: false
                clip: false
                layer.enabled: true
                fillMode: Image.PreserveAspectFit

                DesignEffect {
                    visible: true
                    effects: [
                        DesignDropShadow {}
                    ]
                    layerBlurRadius: 0
                    layerBlurVisible: true
                }
            }

            GroupItem {
                id: passwordGrp
                x: 735
                y: 371

                TextInput {
                    id: txtPwdIn
                    x: 0
                    y: 0
                    width: 300
                    height: 43
                    opacity: 1
                    color: "#3e000000"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    echoMode: TextInput.Normal
                    z: 1
                    onSelectByMouseChanged: txtPwdIn.text = ""
                    mouseSelectionMode: TextInput.SelectCharacters
                    leftPadding: 35
                    font.weight: Font.Normal
                    text: "Password"
                    onTextChanged: if (Login)
                        Login.password = text
                }

                Rectangle {
                    id: rectangle3
                    x: 0
                    y: 0
                    width: 338
                    height: 42
                    opacity: 1
                    color: "#ffffff"
                    radius: 10
                    border.width: 0
                    z: 0
                    rotation: 0
                }

                Image {
                    id: image2
                    x: 0
                    y: 4
                    width: 30
                    height: 34
                    source: "../assets/login imgs/lock.png"
                    fillMode: Image.PreserveAspectFit
                }

                GroupItem {
                    id: eye
                    x: 306
                    y: 10
                    z: 1

                    MouseArea {
                        id: mouseArea1
                        x: 4
                        y: 4
                        width: 20
                        height: 19
                        z: 0
                        cursorShape: Qt.PointingHandCursor

                        onClicked: {
                            image3.visible = !image3.visible;
                            image4.visible = !image4.visible;
                            txtPwdIn.echoMode = (txtPwdIn.echoMode === TextInput.Password) ? TextInput.Normal : TextInput.Password;
                        }
                    }

                    Image {
                        id: image3
                        x: 4
                        y: 4
                        width: 20
                        height: 19
                        visible: true
                        source: "../assets/login imgs/eye.png"
                        fillMode: Image.PreserveAspectFit
                    }

                    Image {
                        id: image4
                        x: 4
                        y: 4
                        width: 20
                        height: 19
                        visible: false
                        source: "../assets/login imgs/closedEye.png"
                        fillMode: Image.PreserveAspectFit
                    }
                }

                MouseArea {
                    id: mouseArea3
                    x: 0
                    y: 0
                    width: 338
                    height: 42
                    z: 1
                    cursorShape: Qt.IBeamCursor

                    onClicked: {
                        rectangle3.border.color = "RoyalBlue";
                        rectangle3.border.width = 2;
                        mouseArea3.z = 0;
                        txtPwdIn.forceActiveFocus();

                        rectangle4.border.color = "#ffffff";
                        rectangle4.border.width = 0;
                        mouseArea2.z = 1;
                    }
                }
            }

            Text {
                id: welcomeBack
                x: 175
                y: 292
                width: 334
                height: 83
                color: "#ffffff"
                text: qsTr("Welcome Back!\n\n")
                font.pixelSize: 50
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                z: 1
                font.family: "Times New Roman"

                Text {
                    id: _text1
                    x: -87
                    y: 57
                    width: 509
                    height: 64
                    color: "#ffffff"
                    text: "To keep connected with us please login with your personal info"
                    font.pixelSize: 20
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    font.family: "Times New Roman"
                }
            }

            AnimatedImage {
                id: animatedImage1
                x: 27
                y: 141
                width: 631
                height: 418
                source: "../assets/login imgs/animation00.gif"
                smooth: true
                opacity: 1

                Timer {
                    id: timer
                    property int i: 0
                    property var images: ["../assets/login imgs/animation00.gif", "../assets/login imgs/animations/an00.gif", "../assets/login imgs/animations/an01.gif", "../assets/login imgs/animations/an02.gif", "../assets/login imgs/animations/an03.gif"]
                    interval: 5000
                    running: true
                    repeat: true
                    onTriggered: i = (i + 1) % images.length
                    onIChanged: animatedImage1.source = images[i]
                }
            }

            DesignEffect {
                effects: [
                    DesignDropShadow {
                        color: "#c6000000"
                        spread: 15
                        blur: 50
                    }
                ]
            }

            GroupItem {
                id: f_pwd
                x: 735
                y: 420

                Text {
                    id: _text2
                    x: 0
                    y: 0
                    width: 100
                    height: 15
                    color: "#ffffff"
                    text: qsTr("Forget Password ?")
                    font.pixelSize: 12
                }

                MouseArea {
                    id: mouseArea
                    x: 0
                    y: 0
                    width: 100
                    height: 16
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onEntered: _text2.font.underline = true
                    onExited: _text2.font.underline = false
                }
            }

            GroupItem {
                id: loginBtn
                x: 811
                y: 481

                Rectangle {
                    id: rectangle1
                    x: 36
                    y: 0
                    width: 114
                    height: 35
                    color: "#9f007b31"
                    radius: 10
                    border.width: 0
                    Behavior on color {
                        ColorAnimation {
                            duration: 300
                        }
                    }
                }

                Text {
                    id: _text
                    x: 36
                    y: 0
                    width: 114
                    height: 35
                    color: "#ffffff"
                    text: qsTr("Login")
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea4
                    x: 38
                    y: 0
                    width: 112
                    height: 35
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onEntered: {
                        _text.text = "";
                        image5.x = 120;
                        rectangle1.color = "#007b31";
                    }

                    onExited: {
                        _text.text = "Login";
                        image5.x = 54;
                        rectangle1.color = "#9f007b31";
                    }

                    onClicked: {
                        if (Login)
                            Login.login();
                    }
                }

                Image {
                    id: image5
                    x: 54
                    y: 10
                    width: 19
                    height: 16
                    source: "../assets/login imgs/login.png"
                    fillMode: Image.PreserveAspectFit

                    Behavior on x {
                        NumberAnimation {
                            duration: 300
                            easing.type: Easing.OutQuad
                        }
                    }
                }
            }
            Text {
                id: statusText
                x: 735
                y: 522
                width: 338
                height: 20
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Timer {
        id: delayTimer
        interval: 2000
        running: false
        repeat: false
        onTriggered: statusText.text = ""
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
