cmake_minimum_required(VERSION 3.10)

project(accel-stream CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

if(NOT DEFINED ACCEL_MODULES_FOLDER)
    set(ACCEL_MODULES_FOLDER "${CMAKE_SOURCE_DIR}/external")
endif()

set(ADDITIONAL_LIBRARIES accel-endianess accel-macros accel-utf8)

include(cmake/FindModule.cmake)
add_accel_module(accel-endianess)
add_accel_module(accel-macros)
add_accel_module(accel-utf8)

add_library(accel-stream INTERFACE)
target_include_directories(accel-stream INTERFACE "include/")
target_link_libraries(accel-stream INTERFACE ${ADDITIONAL_LIBRARIES})

if(ACCEL_BUILD_TESTS)
    add_subdirectory(tests)
endif()