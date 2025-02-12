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
        source: "../../../../../../Downloads/abstract-background-1920x1080-11753.jpeg"

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
                    id: textInput2
                    x: 0
                    y: 0
                    width: 338
                    height: 43
                    opacity: 1
                    color: "#3e000000"
                    text: "Username"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    z: 1
                    mouseSelectionMode: TextInput.SelectCharacters
                    leftPadding: 5
                    font.weight: Font.Normal
                    echoMode: TextInput.Normal
                }

                Rectangle {
                    id: rectangle4
                    x: 0
                    y: 1
                    width: 338
                    height: 42
                    opacity: 0.5
                    color: "#ffffff"
                    radius: 10
                    z: 0
                    rotation: 0
                }
            }

            Image {
                id: image
                x: 854
                y: 141
                width: 100
                height: 100
                source: "../../../../Projects/Astra/doc/imgs/logo.png"
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

            Button {
                id: button
                x: 854
                y: 450
                opacity: 0.5
                text: qsTr("Button")
                anchors.left: image.left
                anchors.right: image.right
                checkable: false
            }

            GroupItem {
                id: passwordGrp
                x: 735
                y: 371
                anchors.horizontalCenter: usernameGrp.horizontalCenter

                TextInput {
                    id: textInput1
                    x: 0
                    y: 0
                    width: 338
                    height: 43
                    opacity: 1
                    color: "#3e000000"
                    text: "Password"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    echoMode: TextInput.Normal
                    z: 1
                    onSelectByMouseChanged: textInput1.text = ""
                    mouseSelectionMode: TextInput.SelectCharacters
                    leftPadding: 5
                    font.weight: Font.Normal
                }

                Rectangle {
                    id: rectangle3
                    x: 0
                    y: 0
                    width: 338
                    height: 42
                    opacity: 0.5
                    color: "#ffffff"
                    radius: 10
                    z: 0
                    rotation: 0
                }
            }

            Text {
                id: _text
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
                source: "../../../../../../Downloads/aaaa.gif"
                paused: false
                speed: 1
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
            }

            MouseArea {
                id: mouseArea
                x: 735
                y: 420
                width: 100
                height: 16
                cursorShape: Qt.PointingHandCursor
            }
        }
    }
}
