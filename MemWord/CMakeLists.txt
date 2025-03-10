cmake_minimum_required(VERSION 3.16)
project(MemWord LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        Sql
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    memword.ui
    memword.h
    memword.cpp

    bookui.cpp
    bookui.h
    bookui.ui

    wordgroupui.cpp
    wordgroupui.h
    wordgroupui.ui

    learnwordgroupwidget.cpp
    learnwordgroupwidget.ui
    learnwordgroupwidget.h

    selectwordwidget.cpp
    selectwordwidget.ui
    selectwordwidget.h

    writesentencewidget.cpp
    writesentencewidget.ui
    writesentencewidget.h

    wordwidget.cpp
    wordwidget.h
    wordwidget.ui

    orgschemadata.cpp
    orgschemadata.h

)

add_subdirectory(dataModule)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql

        mem_lib
)
