cmake_minimum_required(VERSION 3.17)
project(ShrineFileSystemMkfs)

set(CMAKE_CXX_STANDARD 20)

FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

add_executable(ShrineFileSystemMkfs mkfs.cpp)
target_link_libraries(ShrineFileSystemMkfs PUBLIC ${Boost_LIBRARIES})