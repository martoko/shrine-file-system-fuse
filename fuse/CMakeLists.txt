cmake_minimum_required(VERSION 3.17)
project(ShrineFileSystemFuse)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")
find_package(FUSE REQUIRED)

include_directories(${FUSE_INCLUDE_DIR})
add_executable(ShrineFileSystemFuse main.cpp)
target_link_libraries(ShrineFileSystemFuse ${FUSE_LIBRARIES})