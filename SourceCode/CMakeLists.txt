cmake_minimum_required(VERSION 3.10.0)


FILE(GLOB_RECURSE SouceFiles *.cpp *.h)


add_executable(${PROJECT_NAME} ${SouceFiles})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Multimedia)

# include headers and link to the SignalAnalysis library
target_include_directories(${PROJECT_NAME} PUBLIC ${SignalAnalysisHeaderDir})
target_link_libraries(${PROJECT_NAME} SignalAnalysis)

IF(WIN32)
	# ensure that all of the required dll files are present for the Windows version
	SET(TargetDlls "Qt5Core.dll;Qt5Cored.dll;Qt5Gui.dll;Qt5Guid.dll;Qt5Widgets.dll;Qt5Widgetsd.dll")
	FOREACH(TargetDll ${TargetDlls})
		file(COPY $ENV{Qt5_DIR}/../../../bin/${TargetDll} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	ENDFOREACH()
ENDIF()