cmake_minimum_required(VERSION 3.17)
project(file_system_fuse)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
find_package(FUSE REQUIRED)

include_directories(${FUSE_INCLUDE_DIR})
add_executable(file_system_fuse main.cpp)
target_link_libraries(file_system_fuse ${FUSE_LIBRARIES})