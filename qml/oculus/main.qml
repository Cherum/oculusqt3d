import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import StereoViewport 1.0
import FileIO 1.0
import OculusReader 1.0

Rectangle {
    id: rectRoot
    property point lensOffsetFromCenter: Qt.point(0,0.0)
    property rect distortion: Qt.rect(1, 0.22, 0.24, 0.0)
    property real aspectRatio: width / height;
    property real fillScale: 1.8;
    width: 1680
    height: 1050

    OculusReader {
        camera: viewportRoot.camera
//        property bool isFirst: true;
//        property double previousPsi: 0;
//        property double previousTheta: 0;
//        property double previousPhi: 0;

//        onPsiChanged: {
//            if(!isFirst) {
//                var deltaTheta = (theta - previousTheta)*180/Math.PI
//                var deltaPsi = (psi - previousPsi)*180/Math.PI
//                var deltaPhi = (phi - previousPhi)*180/Math.PI
//                deltaPhi = 0;
//                viewportRoot.camera.tiltPanRollEye(-deltaPsi, -deltaTheta, -deltaPhi)
//            }

//            previousPhi = phi
//            previousTheta = theta
//            previousPsi = psi

//            isFirst = false;
//        }
    }

    StereoViewport {
        id: viewportRoot
        fillColor: "black"
        width: rectRoot.width * 1.8
        height: rectRoot.height * 1.8 // TODO: Check real ratio
        stereoType: StereoViewport.RightLeft
        light: Light {
            position: Qt.vector3d(2.0, 1.0, 3.0)
        }

        camera: Camera {
            nearPlane: 0.5
            farPlane: 1000
            fieldOfView: 90
            center: Qt.vector3d(1,0,0)
            eye: Qt.vector3d(5,0,0)
            eyeSeparation: 0.1
        }

        Cube {
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            x: 1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            y: 1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            z: 1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            x: -4
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            x: -1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            y: -1.5
            effect: Effect {
                color: "yellow"
            }
        }

        Cube {
            z: -1.5
            effect: Effect {
                color: "yellow"
            }
        }
    }

    FileIO {
        id: vertexShaderFile
        source: "oculus.vert"
        onError: console.log(msg)
    }

    FileIO {
        id: fragmentShaderFile
        source: "oculus.frag"
        onError: console.log(msg)
    }

    ShaderEffectSource {
        id: shaderEffectSourceLeft
        width: rectRoot.width / 2
        anchors {
            left: rectRoot.left
            top: rectRoot.top
            bottom: rectRoot.bottom
        }
        visible: false

        hideSource: true
        sourceItem: viewportRoot
        sourceRect: Qt.rect(0, 0, viewportRoot.width / 2, viewportRoot.height)
    }

    ShaderEffectSource {
        id: shaderEffectSourceRight
        width: rectRoot.width / 2
        anchors {
            right: rectRoot.right
            top: rectRoot.top
            bottom: rectRoot.bottom
        }
        visible: false

        hideSource: true
        sourceItem: viewportRoot
        sourceRect: Qt.rect(viewportRoot.width / 2, 0, viewportRoot.width / 2, viewportRoot.height)
    }

    Item {
        width: rectRoot.width / 2
        anchors {
            left: rectRoot.left
            top: rectRoot.top
            bottom: rectRoot.bottom
        }
        clip: true
        ShaderEffect {
            width: parent.width + 100
            height: parent.height
            x: 0

            property variant qt_Texture0: shaderEffectSourceLeft
            property point lensOffsetFromCenter: rectRoot.lensOffsetFromCenter
            property rect distortion: rectRoot.distortion
            property real aspectRatio: rectRoot.aspectRatio
            property real fillScale: rectRoot.fillScale
            vertexShader: vertexShaderFile.read()
            fragmentShader: fragmentShaderFile.read()
        }
    }

    Item {
        width: rectRoot.width / 2
        anchors {
            right: rectRoot.right
            top: rectRoot.top
            bottom: rectRoot.bottom
        }
        clip: true
        ShaderEffect {
            width: parent.width + 100
            height: parent.height
            x: -100

            property variant qt_Texture0: shaderEffectSourceRight
            property point lensOffsetFromCenter: Qt.point(-rectRoot.lensOffsetFromCenter.x, rectRoot.lensOffsetFromCenter.y)
            property rect distortion: rectRoot.distortion
            property real aspectRatio: rectRoot.aspectRatio
            property real fillScale: rectRoot.fillScale
            vertexShader: vertexShaderFile.read()
            fragmentShader: fragmentShaderFile.read()
        }
    }
}
