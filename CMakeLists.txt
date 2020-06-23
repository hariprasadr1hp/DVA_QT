cmake_minimum_required(VERSION 3.5)

set(This result)

project(${This}
    LANGUAGES CXX
)

######################################################
#environmental variables

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

######################################################

#modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")

#######################################################
#for Qt
message("------------------------------------")
message("---- LOADING Qt...")
find_package(Qt5 COMPONENTS Widgets Core Gui PrintSupport REQUIRED)

if (${Qt5_FOUND})
    message("-- Qt5_VERSION: ${Qt5_VERSION}")
else()
    message("-- Qt5 NOT FOUND!")
endif()

add_definitions(${QT_DEFINITIONS})

set(QT5_LIBRARIES
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::PrintSupport
)

include_directories(${QT_INCLUDES})

get_target_property(QtCore_location Qt5::Core LOCATION)

add_subdirectory(lib)

add_executable(${This} lib/main.cpp)

target_link_libraries (${This}
    dva
    ${QT5_LIBRARIES}
)

