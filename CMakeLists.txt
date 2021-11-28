cmake_minimum_required(VERSION 3.12)

project(TypRua
        VERSION "2.0.0"
        DESCRIPTION "TypRua - Yet another markdown editor."
        LANGUAGES CXX)

set(CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/cmake
        ${CMAKE_MODULE_PATH}
        ${ECM_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Qt Libraries and Definitions
set(QT_MIN_VERSION 5.8.0)
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui Widgets Network Sql WebEngine)

if (HAVE_X11)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS X11Extras)
    find_package(Qt5DBus ${QT_MIN_VERSION})
endif ()
if (APPLE)
    find_package(Qt5 REQUIRED COMPONENTS MacExtras)
endif ()
if (WIN32)
    find_package(Qt5 REQUIRED COMPONENTS WinExtras)
endif ()
set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Network Qt5::Sql Qt5::WebEngine)

if (Qt5DBus_FOUND)
    set(QT_LIBRARIES ${QT_LIBRARIES} Qt5::DBus)
    get_target_property(QT_DBUSXML2CPP_EXECUTABLE Qt5::qdbusxml2cpp LOCATION)
endif ()
if (HAVE_X11)
    set(QT_LIBRARIES ${QT_LIBRARIES} Qt5::X11Extras)
endif ()
if (WIN32)
    set(QT_LIBRARIES ${QT_LIBRARIES} Qt5::WinExtras)
endif ()
if (NOT WIN32)
    find_package(Qt5DBus REQUIRED)
    set(QT_LIBRARIES ${QT_LIBRARIES} Qt5::DBus)
    add_definitions(-DQt5DBus_FOUND)
endif ()

add_definitions(${QT_DEFINITIONS})

add_subdirectory(src)

