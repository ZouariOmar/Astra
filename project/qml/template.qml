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
    id: root
    width: 1920
    height: 1080

    Rectangle {
        id: rectangle
        x: -24
        y: 0
        width: 356
        height: 1080
        color: "#c8d9e6"
        radius: 20

        Image {
            id: image
            x: 45
            y: 12
            width: 100
            height: 100
            source: "../Documents/Daily/Projects/Astra/doc/imgs/logo.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: _text
            x: 135
            y: 30
            width: 169
            height: 64
            text: qsTr("Astra")
            font.pixelSize: 55
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Times New Roman"
        }

        Column {
            id: column
            x: 24
            y: 199
            width: 296
            height: 457

            GroupItem {
                id: option

                Rectangle {
                    id: rectangle2
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    color: "#00007b31"
                    border.width: 0
                }

                Text {
                    id: _text2
                    x: 71
                    y: 18
                    width: 260
                    height: 42
                    color: "#494d53"
                    text: qsTr("Boutiques")
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea4
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    Connections {
                        target: mouseArea4
                        onExited: {
                            rectangle2.color = "#00007b31";
                        }
                        onEntered: {
                            rectangle2.color = "#e4ecf2";
                        }
                        onReleased: {
                            rectangle2.color = "#e4ecf2";
                        }
                        onPressed: {
                            rectangle2.color = "#2f4156";
                        }
                    }
                }

                Image {
                    id: image5
                    x: 21
                    y: 16
                    width: 44
                    height: 44
                    source: "icons8-shop-50.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            GroupItem {
                id: option1
                Rectangle {
                    id: rectangle3
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    color: "#00007b31"
                    border.width: 0
                }

                Text {
                    id: _text3
                    x: 71
                    y: 18
                    width: 260
                    height: 42
                    color: "#494d53"
                    text: qsTr("Commerçant")
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea5
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    hoverEnabled: true
                    Connections {
                        target: mouseArea5
                        onReleased: {
                            rectangle3.color = "#e4ecf2";
                        }
                        onPressed: {
                            rectangle3.color = "#2f4156";
                        }
                        onExited: {
                            rectangle3.color = "#00007b31";
                        }
                        onEntered: {
                            rectangle3.color = "#e4ecf2";
                        }
                    }
                    cursorShape: Qt.PointingHandCursor
                }

                Image {
                    id: image6
                    x: 21
                    y: 16
                    width: 44
                    height: 44
                    source: "icons8-salesman-50.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            GroupItem {
                id: option2
                Rectangle {
                    id: rectangle4
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    color: "#00007b31"
                    border.width: 0
                }

                Text {
                    id: _text4
                    x: 71
                    y: 18
                    width: 260
                    height: 42
                    color: "#494d53"
                    text: qsTr("Partennariats")
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea6
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    hoverEnabled: true
                    Connections {
                        target: mouseArea6
                        onReleased: {
                            rectangle4.color = "#e4ecf2";
                        }
                        onPressed: {
                            rectangle4.color = "#2f4156";
                        }
                        onExited: {
                            rectangle4.color = "#00007b31";
                        }
                        onEntered: {
                            rectangle4.color = "#e4ecf2";
                        }
                    }
                    cursorShape: Qt.PointingHandCursor
                }

                Image {
                    id: image7
                    x: 21
                    y: 16
                    width: 44
                    height: 44
                    source: "icons8-handshake-50.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            GroupItem {
                id: option3
                Rectangle {
                    id: rectangle5
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    color: "#00007b31"
                    border.width: 0
                }

                Text {
                    id: _text5
                    x: 71
                    y: 18
                    width: 260
                    height: 42
                    color: "#494d53"
                    text: qsTr("Événement")
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea7
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    hoverEnabled: true
                    Connections {
                        target: mouseArea7
                        onReleased: {
                            rectangle5.color = "#e4ecf2";
                        }
                        onPressed: {
                            rectangle5.color = "#2f4156";
                        }
                        onExited: {
                            rectangle5.color = "#00007b31";
                        }
                        onEntered: {
                            rectangle5.color = "#e4ecf2";
                        }
                    }
                    cursorShape: Qt.PointingHandCursor
                }

                Image {
                    id: image8
                    x: 21
                    y: 16
                    width: 44
                    height: 44
                    source: "icons8-event-50.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            GroupItem {
                id: option4
                Rectangle {
                    id: rectangle6
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    color: "#00007b31"
                    border.width: 0
                }

                Text {
                    id: _text6
                    x: 71
                    y: 18
                    width: 260
                    height: 42
                    color: "#494d53"
                    text: qsTr("Personnels")
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea8
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    hoverEnabled: true
                    Connections {
                        target: mouseArea8
                        onReleased: {
                            rectangle6.color = "#e4ecf2";
                        }
                        onPressed: {
                            rectangle6.color = "#2f4156";
                        }
                        onExited: {
                            rectangle6.color = "#00007b31";
                        }
                        onEntered: {
                            rectangle6.color = "#e4ecf2";
                        }
                    }
                    cursorShape: Qt.PointingHandCursor
                }

                Image {
                    id: image9
                    x: 21
                    y: 16
                    width: 44
                    height: 44
                    source: "icons8-user-groups-48.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            GroupItem {
                id: option5
                Rectangle {
                    id: rectangle7
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    color: "#00007b31"
                    border.width: 0
                }

                Text {
                    id: _text7
                    x: 71
                    y: 18
                    width: 260
                    height: 42
                    color: "#494d53"
                    text: qsTr("Employés")
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    id: mouseArea9
                    x: 0
                    y: 0
                    width: 331
                    height: 76
                    hoverEnabled: true
                    Connections {
                        target: mouseArea9
                        onReleased: {
                            rectangle7.color = "#e4ecf2";
                        }
                        onPressed: {
                            rectangle7.color = "#2f4156";
                        }
                        onExited: {
                            rectangle7.color = "#00007b31";
                        }
                        onEntered: {
                            rectangle7.color = "#e4ecf2";
                        }
                    }
                    cursorShape: Qt.PointingHandCursor
                }

                Image {
                    id: image10
                    x: 21
                    y: 16
                    width: 44
                    height: 44
                    source: "icons8-employees-24.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    ToolSeparator {
        id: toolSeparator
        x: 148
        y: 75
        width: 13
        height: 150
        rotation: 90
    }

    ToolSeparator {
        id: toolSeparator1
        x: 149
        y: 637
        width: 13
        height: 150
        rotation: 90
    }

    Text {
        id: _text1
        x: 12
        y: 954
        width: 91
        height: 30
        text: qsTr("Terms")
        font.pixelSize: 20
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: _text8
        x: 109
        y: 954
        width: 91
        height: 30
        text: qsTr("Support")
        font.pixelSize: 20
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        id: _text9
        x: 206
        y: 954
        width: 92
        height: 30
        text: qsTr("Privacy")
        font.pixelSize: 20
        verticalAlignment: Text.AlignVCenter
    }
}
