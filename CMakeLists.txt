cmake_minimum_required(VERSION 3.28)

project(qt-treeview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(TARGET_NAME ${CMAKE_PROJECT_NAME}_app)

option(USE_MOCK_PROVIDER "Use mock data provider instead of real SQLite" OFF)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(res)

set(SOURCES
        src/main.cpp
        src/om_data_model.cpp
        src/om_tree_delegate.cpp
        src/om_tree_view.cpp
)

set(HEADERS
        src/om_data_model.h
        src/om_tree_delegate.h
        src/om_tree_view.h
        src/dataproviders/i_om_data_provider.h
        src/om_data_provider_injector.h
)

if(USE_MOCK_PROVIDER)
    list(APPEND SOURCES src/tests/mock_data_provider_om_filled.cpp)
    list(APPEND HEADERS src/tests/mock_data_provider_om_filled.h)
else()
    list(APPEND SOURCES src/dataproviders/sqlite_om_data_provider.cpp)
    list(APPEND HEADERS src/dataproviders/sqlite_om_data_provider.h)
endif()

qt_add_executable(${TARGET_NAME}
        ${SOURCES}
        ${HEADERS}
)

if(USE_MOCK_PROVIDER)
    target_compile_definitions(${TARGET_NAME} PRIVATE USE_MOCK_DATA_PROVIDER)
endif()

target_link_libraries(${TARGET_NAME} PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql
        app_resources
)