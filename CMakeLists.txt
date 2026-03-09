cmake_minimum_required(VERSION 3.28)

project(qt-treeview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TARGET_NAME ${CMAKE_PROJECT_NAME}_app)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml)

qt_standard_project_setup(REQUIRES 6.5)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl
)

qt_add_executable(${TARGET_NAME}
        ${SOURCES}
        ${HEADERS}
)

target_link_libraries(${TARGET_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
)