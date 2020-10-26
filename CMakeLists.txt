cmake_minimum_required(VERSION 3.8)

project(ECS VERSION 0.1.0 LANGUAGES CXX)

add_executable(ECS_Example
    src/main.cpp
    src/Systems/Move.cpp
    src/Systems/Print.cpp
)

target_compile_options(ECS_Example PRIVATE "-std=c++17")

target_include_directories(ECS_Example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)