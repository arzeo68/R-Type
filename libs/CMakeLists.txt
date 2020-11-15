cmake_minimum_required(VERSION 3.17.0)

set(LIB_INSTALL_PATH ${CMAKE_SOURCE_DIR}/ressources/ennemies)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/Client)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)
include_directories(${CONAN_INCLUDE_DIRS})

add_library(BasicShipFactory
    SHARED
    ../src/Server/EntityLib/IEntityFactory.hpp
    ../src/Server/EntityLib/BasicShipFactory.hpp
    ../src/Server/EntityLib/BasicShipFactory.cpp)
set_target_properties(BasicShipFactory PROPERTIES LINKER_LANGUAGE CXX)

add_library(MediumShipFactory
    SHARED
    ../src/Server/EntityLib/IEntityFactory.hpp
    ../src/Server/EntityLib/MediumShipFactory.hpp
    ../src/Server/EntityLib/MediumShipFactory.cpp)
set_target_properties(BasicShipFactory PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS BasicShipFactory DESTINATION ${LIB_INSTALL_PATH})