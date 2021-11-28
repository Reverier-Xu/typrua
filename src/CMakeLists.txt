cmake_minimum_required(VERSION 3.12)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/app_config.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/app_config.h"
)

file(GLOB MODELS_SRCS "models/*.cxx")
file(GLOB MODELS_HEADERS "models/*.h")

file(GLOB MANAGERS_SRCS "managers/*.cxx")
file(GLOB MANAGERS_HEADERS "managers/*.h")

file(GLOB STORAGE_SRCS "storage/*.cxx")
file(GLOB STORAGE_HEADERS "storage/*.h")

qt5_add_resources(RESOURCES "resources/main.qrc")

set(SRCS 
    ${MODELS_SRCS}
    ${MANAGERS_SRCS}
    ${STORAGE_SRCS}
    ${RESOURCES}
    entry.cxx)

set(HEADERS
    ${MODELS_HEADERS}
    ${MANAGERS_HEADERS}
    ${STORAGE_HEADERS})

add_executable(${PROJECT_NAME} ${HEADERS} ${SRCS})

target_link_libraries(${PROJECT_NAME}
    ${QT_LIBRARIES})

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        AUTOUIC ON
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
