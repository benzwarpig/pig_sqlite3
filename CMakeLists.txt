cmake_minimum_required(VERSION 3.12)

project(pig_sqlite3 VERSION 1.0)

if(NOT EXISTS ./data)
    file(MAKE_DIRECTORY ./data)
endif()

add_compile_options(-std=c++14)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    third_lib/sqlite_orm/include
    common
    inc
    tool
)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/pig_sqlite.cpp
    src/sqlite_handle.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    sqlite3
)

set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(TOOL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tool)
message(STATUS "tool dir =${TOOL_DIR}")
execute_process(COMMAND sh ${TOOL_DIR}/make_version.sh)

configure_file(
    "${PROJECT_SOURCE_DIR}/tool/build_info.h.in"
    "${PROJECT_SOURCE_DIR}/tool/build_info.h")
