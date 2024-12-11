

cmake_minimum_required(VERSION 3.5)

project(dataModule)

set(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set(current_dir "${WORKING_DIRECTORY}/MemWord/dataModule")

file(GLOB_RECURSE HEADERS "${current_dir}/header/*.h")
file(GLOB_RECURSE SOURCES "${current_dir}/src/*.cpp")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS  
        Core  
        Gui  
        Widgets  
        Sql  
)

#message("----------------------------------------${HEADERS}")
#message("----------------------------------------${SOURCES}")


#message("Qt version: ${Qt${QT_VERSION_MAJOR}_VERSION}")

add_library(mem_lib STATIC)
target_sources(mem_lib PRIVATE ${SOURCES} ${HEADERS})

target_include_directories(mem_lib PUBLIC "${current_dir}/header")
target_include_directories(mem_lib PUBLIC ${Qt${QT_VERSION_MAJOR}_INCLUDE_DIRS})

target_link_libraries(mem_lib  
    PUBLIC  
        Qt::Core  
        Qt::Gui  
        Qt::Widgets  
        Qt::Sql  
)