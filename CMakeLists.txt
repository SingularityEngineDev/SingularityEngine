cmake_minimum_required(VERSION 3.21)

project(SingularityEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_filename_component(SNGL_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(examples)