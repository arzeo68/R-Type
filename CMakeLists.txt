if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif ()

cmake_minimum_required(VERSION 3.5.1)
project(RType)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/bin)
set(CMAKE_CXX_STANDARD 20)


# Find SFML
#set(SFML_STATIC_LIBRARIES TRUE)
#find_package(SFML REQUIRED COMPONENTS audio graphics window system)
#include_directories(${SFML_INCLUDE_DIR})

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS}")
else()
    set(STANDARD_UNIX_CXX_FLAGS "-Wall -g3 -Wextra -Wfatal-errors")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STANDARD_UNIX_CXX_FLAGS}")
endif()

if (EXISTS conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
else()
    message(FATAL_ERROR "No conanbuildinfo.cmake file found please create a directory named \"build\" at the root of the repository then go inside your build folder and execute the following command \nconan install .. --build=missing")
endif()

conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_executable(GraphECS
    src/main.cpp
    src/Systems/RenderSystem.cpp
)

target_include_directories(GraphECS PRIVATE ./src)

if (MSVC)
    set_target_properties(GraphECS PROPERTIES LINK_FLAGS /MACHINE:X64)
endif()

install(TARGETS GraphECS DESTINATION ${PROJECT_SOURCE_DIR}/bin)

#############################################################
target_link_libraries(GraphECS ${CONAN_LIBS})
#############################################################
message(${CONAN_INCLUDE_DIRS})