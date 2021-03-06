cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(OculusQt3D)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC TRUE)

SET(CMAKE_PREFIX_PATH C:/Qt/5.2.1_msvc2010_opengl/5.2.1/msvc2010_opengl)	
find_package(Qt5 REQUIRED Core Gui OpenGL Script Widgets 3D 3DQuick Qml Quick)
find_package(OpenGL)

INCLUDE_DIRECTORIES(
	multibillboard
	flymodenavigator-qt3d
	
	qml
	qtquick2applicationviewer
	src
	
	OculusSDK/LibOVR/Include
)

link_directories(
	/OculusSDK/LibOVR/Lib/Win32
)

add_subdirectory(multibillboard)
add_subdirectory(flymodenavigator-qt3d)
#add_subdirectory(OculusSDK/LibOVR)

set(OCSOURCE
	src/fileio.cpp
	src/fileio.h
	src/frameratecounter.cpp
	src/frameratecounter.h
	src/main.cpp
	src/mdstate.cpp
	src/mdstate.h
	src/mdstatemanager.cpp
	src/mdstatemanager.h
	src/oculusreader.cpp
	src/oculusreader.h
	src/oculusview.cpp
	src/oculusview.h
	src/qgldrawbuffersurface.cpp
	src/qgldrawbuffersurface_p.h
	src/qglmaskedsurface.cpp
	src/qglmaskedsurface_p.h
	src/screeninfo.cpp
	src/screeninfo.h
	src/screeninfoscreen.cpp
	src/screeninfoscreen.h
	src/settings.cpp
	src/settings.h
	src/stereoviewport.cpp
	src/stereoviewport.h
	
	qtquick2applicationviewer/qtquick2applicationviewer.cpp
	qtquick2applicationviewer/qtquick2applicationviewer.h
)
add_executable(
	OculusQt3D src/main.cpp ${OCSOURCE} ${BILLBOARD_SOURCE}
)

TARGET_LINK_LIBRARIES(OculusQt3D
	#Qt5::Declarative
	Qt5::Script
	#Qt5::Xml
	Qt5::OpenGL
	Qt5::Widgets
	Qt5::Gui
	Qt5::Core
	Qt5::3D
	Qt5::3DQuick
	Qt5::Qml
	Qt5::Quick
	
	MultiBillboard
	FlyModeNavigator
	
	${OPENGL_LIBRARIES}
	debug libovrd.lib
	optimized libovr.lib
)
