import QtQuick 2.7
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.4

Slider {
    id: root

    // Component properties
    implicitWidth: 200
    implicitHeight: 40
    from: 0
    to: 0
    stepSize: 1
    state: "stopped"

    // Volume bar properties, functions & events
    property bool isLooped: false
    property bool isPlayRegionEnabled: false
    property int playRegionBegin: 0
    property int playRegionEnd: 0
    property int elapsedTime: 0
    property int duration: 0

    states: [
        State {
            name: "stopped"
            PropertyChanges { target: sliderHandle; color: "#6AFF0000" }
            PropertyChanges { target: repeatIcon; color: "#000000" }
            PropertyChanges { target: foregroundBar; color: "red" }
            PropertyChanges {
                target: trackTimeElapsed
                color: (sliderHandle.x >= sliderHandle.width + 8 ? "white" : "black")
            }
            PropertyChanges {
                target: trackTimeRemaining
                color: (sliderHandle.x + sliderHandle.width >= parent.width - this.width - 5 ? "white" : "black")
            }
        },
        State {
            name: "paused"
            PropertyChanges { target: sliderHandle; color: "#80FFFF00" }
            PropertyChanges { target: repeatIcon; color: "#000000" }
            PropertyChanges { target: foregroundBar; color: "yellow" }
            PropertyChanges { target: trackTimeElapsed; color: "black" }
            PropertyChanges { target: trackTimeRemaining; color: "black" }
        },
        State {
            name: "playing"
            PropertyChanges { target: sliderHandle; color: "#6A00FF00" }
            PropertyChanges { target: repeatIcon; color: "#000000" }
            PropertyChanges { target: foregroundBar; color: "green" }
            PropertyChanges {
                target: trackTimeElapsed
                color: (sliderHandle.x >= sliderHandle.width + 8 ? "white" : "black")
            }
            PropertyChanges {
                target: trackTimeRemaining
                color: (sliderHandle.x + sliderHandle.width >= parent.width - this.width - 5 ? "white" : "black")
            }
        }
    ]

    transitions: [
        Transition {
            from: "stopped"; to: "playing"
            ColorAnimation { target: sliderHandle; properties: "color"
                from: "#6AFF0000"; to: "#6A00FF00"; duration: 150
            }
            ColorAnimation { target: foregroundBar; properties: "color"
                from: "red"; to: "green"; duration: 150
            }
        },
        Transition {
            from: "stopped"; to: "paused"
            ColorAnimation { target: sliderHandle; properties: "color"
                from: "#6AFF0000"; to: "#80FFFF00"; duration: 150
            }
            ColorAnimation { target: foregroundBar; properties: "color"
                from: "red"; to: "yellow"; duration: 150
            }
        },
        Transition {
            from: "playing"; to: "paused"
            ColorAnimation { target: sliderHandle; properties: "color"
                from: "#6A00FF00"; to: "#80FFFF00"; duration: 150
            }
            ColorAnimation { target: foregroundBar; properties: "color"
                from: "green"; to: "yellow"; duration: 150
            }
        },
        Transition {
            from: "playing"; to: "stopped"
            ColorAnimation { target: sliderHandle; properties: "color"
                from: "#6A00FF00"; to: "#6AFF0000"; duration: 150
            }
            ColorAnimation { target: foregroundBar; properties: "color"
                from: "green"; to: "red"; duration: 150
            }
        },
        Transition {
            from: "paused"; to: "playing"
            ColorAnimation { target: sliderHandle; properties: "color"
                from: "#80FFFF00"; to: "#6A00FF00"; duration: 150
            }
            ColorAnimation { target: foregroundBar; properties: "color"
                from: "yellow"; to: "green"; duration: 150
            }
        },
        Transition {
            from: "paused"; to: "stopped"
            ColorAnimation { target: sliderHandle; properties: "color"
                from: "#80FFFF00"; to: "#6AFF0000"; duration: 150
            }
            ColorAnimation { target: foregroundBar; properties: "color"
                from: "yellow"; to: "red"; duration: 150
            }
        }
    ]

    onElapsedTimeChanged: {
        root.value = root.elapsedTime;
    }

    onDurationChanged: {
        root.to = root.duration;
    }


    function timeElapsed(elapsedMs){
        if (elapsedMs <= 0)
            return "+00:00";
        var elapsed = elapsedMs
        var ms = elapsed % 1000;
        elapsed = (elapsed - ms) / 1000;
        var secs = elapsed % 60;
        var mins = (elapsed - secs) / 60;

        return "+" + ("00" + mins).slice(-2) + ':' + ("00" + secs).slice(-2);
    }

    function timeRemaining(elapsedMs, durationMs) {
        if(durationMs <= 0)
            return "-00:00";
        var remaining = durationMs - elapsedMs;

        var ms = remaining % 1000;
        remaining = (remaining - ms) / 1000;
        var secs = remaining % 60;
        var mins = (remaining - secs) / 60;

        return "-" + ("00" + mins).slice(-2) + ':' + ("00" + secs).slice(-2);
    }

    // Component UI

    handle: Rectangle {
        id: sliderHandle
        x: root.visualPosition * (root.width - width)
        y: (root.height - height) / 2
        width: 45
        height: root.height
        border.color: "white"
        border.width: 2
        //color: "#414345"
        /*
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#414345" }
            GradientStop { position: 1.0; color: "#232526" }
        }*/

        Image {
            id: loopStateImage
            width: Math.floor(0.6 * sliderHandle.width); height: Math.floor(0.6 * sliderHandle.height)
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            source: '/qml/icons/loop.png'
            visible: root.isLooped
        }

        ColorOverlay {
            id: repeatIcon
            anchors.fill: loopStateImage; source: loopStateImage
            visible: root.isLooped
        }
    }

    background: Item {
        id: background
        y: (root.height - height) / 2
        width: root.width; height: 20

        Rectangle {
            id: playRegion
            x: (root.playRegionBegin <= 0 || root.duration <= 0) ? 0 : root.width * root.playRegionBegin / root.duration
            y: -20
            width: (root.playRegionEnd <= 0 || root.duration <= 0) ? 0 : root.width * (root.playRegionEnd - root.playRegionBegin) / root.duration
            height: root.height + 20
            opacity: 0.8
            color: "blue"
            visible: root.isPlayRegionEnabled
        }

        Rectangle {
                id: backgroundBar
                width: root.width; height: 20
                border.color: "white"
                border.width: 2
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#cfcfcf" }
                    GradientStop { position: 1.0; color: "#9e9e9e" }
                }
        }

        Rectangle {
            id: foregroundBar
            width: root.visualPosition * parent.width
            height: 20
            border.color: "white"
            border.width: 2
        }

        Rectangle {
            id: playRegionPosition
            x: root.visualPosition * (root.width - width/2); y: -20
            width: 5; height: root.height + 20
            opacity: 0.9
            color: "yellow"
            visible: root.isPlayRegionEnabled
        }

        Text {
             id: trackTimeElapsed
             x: (sliderHandle.x >= sliderHandle.width + 8 ? 5 : sliderHandle.x + sliderHandle.width + 5)
             y: Math.floor((parent.height - this.height) / 2)
             color: (sliderHandle.x >= sliderHandle.width + 8 ? "white" : "black")
             font.family: "Helvetica"
             font.bold: true
             font.pointSize: 14
             text: timeElapsed(root.elapsedTime)
        }


        Text {
             id: trackTimeRemaining
             x: (sliderHandle.x + sliderHandle.width >= parent.width - this.width - 5 ? sliderHandle.x - this.width - 5 : parent.width - this.width - 5)
             y: Math.floor((parent.height - this.height) / 2)
             color: (sliderHandle.x + sliderHandle.width >= parent.width - this.width - 5 ? "white" : "black")
             font.family: "Helvetica"
             font.bold: true
             font.pointSize: 14
             text: timeRemaining(root.elapsedTime, root.duration)
        }
    }
}
