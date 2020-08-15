cmake_minimum_required(VERSION 3.0.0)
project(Reverser)

file(GLOB_RECURSE _SOURSCES "*.cpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC ${_SOURSCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)