if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif ()

cmake_minimum_required(VERSION 3.5.1)
project(RType)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/bin)
set(CMAKE_CXX_STANDARD 17)


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

#include(CMakeSources.cmake)

conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)


# UI.h  PATH

add_executable(r-type_client Client/main.cpp Client/src/window/Window.cpp Client/include/window/Window.hpp Client/src/window/AWindow.cpp Client/include/window/AWindow.hpp)
add_executable(r-type_server Server/main.cpp)

if (MSVC)
    set_target_properties(r-type_client PROPERTIES LINK_FLAGS /MACHINE:X64)
    set_target_properties(r-type_server PROPERTIES LINK_FLAGS /MACHINE:X64)
endif()

install(TARGETS r-type_client DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS r-type_server DESTINATION ${PROJECT_SOURCE_DIR}/bin)

#############################################################
target_link_libraries(r-type_client ${CONAN_LIBS})
#############################################################
target_link_libraries(r-type_server ${CONAN_LIBS})
message(${CONAN_LIBS})