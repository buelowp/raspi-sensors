cmake_minimum_required (VERSION 3.2.0)
project (linux-sensors)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
FILE (GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")
FILE (GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_library (${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories (${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
