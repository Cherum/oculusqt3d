oculusqt3d
==========

Example of stereoscopic viewing for Oculus Rift with QML and Qt3D.

I'm testing this build under Win7 with Visual Studio 2010 and Qt5.2.

For help installing QT3D to QT5.2 see this link: http://qt-project.org/wiki/Qt3D-Installation
If Qt3D won't compile because of ReadPixels() not being part of the context, remove the call via context and just use the OpenGl function.

If you try to build the project after the Qt3D installation, you will get an error that QT5.3 is missing.
QT3D looks for Qt5.3, just change the references in the mentioned CMakeLists.txt to QT5.2 and it will build.