oculusqt3d
==========

Example of stereoscopic viewing for Oculus Rift with QML and Qt3D.

I'm testing this build under Win7 with Visual Studio 2010 and Qt5.2.

For help installing QT3D to QT5.2 see this link: http://qt-project.org/wiki/Qt3D-Installation
If you try to build the project after the Qt3D installation, you will get an error that QT5.3 is missing.
QT3D looks for Qt5.3 in a CMake file, just change the references to QT5.2 and it will build.