cmake_minimum_required(VERSION 3.15)

project(ttmd-cli VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ttmd.cpp
)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(ttmd-cli ${SOURCE_FILES})