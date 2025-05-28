cmake_minimum_required(VERSION 3.6.0)

project(glacier-welcome
	VERSION 0.1
	DESCRIPTION "The Glacier welcome screen")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FeatureSummary)
include(GNUInstallDirs)
include(FindPkgConfig)

set(CMAKE_INSTALL_PREFIX /usr)
set(QT_MIN_VERSION "6.0.0")
find_package(Qt6 COMPONENTS Gui Qml Quick DBus LinguistTools REQUIRED)
find_package(Glacier 0.9.0 COMPONENTS App REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLACIERPASSWORD glacierdevicepassword REQUIRED IMPORTED_TARGET)

add_subdirectory(src)

install(FILES data/glacier-welcome.service DESTINATION /usr/lib/systemd/system)
