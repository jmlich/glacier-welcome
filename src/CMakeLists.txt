set(PROJECT
    glacier-welcome)

set(SRC 
    main.cpp
)

qt6_add_resources(RESOURCES qml/${PROJECT}.qrc)

add_executable(${PROJECT} ${SRC} ${RESOURCES}
    welcome.h welcome.cpp)

include_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT}
	Qt6::Gui
	Qt6::Qml
	Qt6::Quick
        Qt6::DBus
        Glacier::App
        PkgConfig::GLACIERPASSWORD)

install(TARGETS ${PROJECT} RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
