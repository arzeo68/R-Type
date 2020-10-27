cmake_minimum_required(VERSION 3.8)

project(ECS VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


add_executable(ECS_Example
    src/main.cpp
    src/Systems/Move.cpp
    src/Systems/Print.cpp
)


target_include_directories(ECS_Example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)