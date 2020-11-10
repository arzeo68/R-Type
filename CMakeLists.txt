if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there")
endif ()

option(BUILD_DOC "Build documentation" OFF)

if (BUILD_DOC)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/Doxyfile.txt)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        add_custom_target(doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating documentation with Doxygen"
                VERBATIM
                )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif(BUILD_DOC)

cmake_minimum_required(VERSION 3.17.0)
project(Rtype)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/bin)
set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS}")
else()
    set(STANDARD_UNIX_CXX_FLAGS "-Wall -g3 -Wextra -Wfatal-errors -std=c++2a")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STANDARD_UNIX_CXX_FLAGS}")
endif()

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
else()
    message(FATAL_ERROR "No conanbuildinfo.cmake file found please create a directory named \"build\" at the root of the repository then go inside your build folder and execute the following command \nconan install .. --build=missing")
endif()

conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(src/Client)
include_directories(src/)

add_executable(r-type_client
        src/Client/main.cpp
        src/Client/Window/Window.cpp
        src/Client/Window/Window.hpp
        src/Client/Window/AWindow.cpp
        src/Client/Window/AWindow.hpp
        src/Client/typeEncapsulation.hpp
        src/Client/RenderTarget/IRenderTarget.hpp
        src/Client/RenderTarget/ARenderTarget.hpp
        src/Client/RenderTarget/RenderTarget.cpp
        src/Client/RenderTarget/RenderTarget.hpp
        src/Client/SceneManager/SceneManager.hpp
        src/Client/SceneManager/SceneManager.cpp
        src/Client/ObserverPattern/Subject.hpp
        src/Client/EventManager/EventManager.hpp
        src/Client/EventManager/SFMLEvents.hpp
        src/Client/EventManager/EventManager.cpp
        src/Client/Application/Application.cpp
        src/Client/Application/Application.hpp
        src/Client/Components/Network.hpp
        src/Client/unique_id.hpp
        src/Client/ClientNetwork/ISocket.hpp
        src/Client/ClientNetwork/ASocket.hpp
        src/Client/ClientNetwork/TcpNetwork.cpp
        src/Client/ClientNetwork/TcpNetwork.hpp
        src/Client/ClientNetwork/UdpNetwork.cpp
        src/Client/ClientNetwork/UdpNetwork.hpp
        src/Common/Network.hpp
        src/Common/Systems/RenderSystem.cpp)
add_executable(r-type_server
        src/Server/Network/Network/INetwork.hpp
        src/Server/Network/Socket/ISocket.hpp
        src/Server/Network/Network/Router.hpp
        src/Server/Network/Network/BoostNetwork.cpp
        src/Server/Network/Network/BoostNetwork.hpp
        src/Server/Network/Network/ANetwork.hpp
        src/Server/Main.cpp
        src/Common/Log.hpp src/Common/Log.cpp
        src/Server/Network/Socket/TCPBoostSocket.cpp
        src/Server/Network/Socket/TCPBoostSocket.hpp
        src/Server/Network/Socket/UDPBoostSocket.cpp
        src/Server/Network/Socket/UDPBoostSocket.hpp
        src/Server/Network/Client/BoostClient.cpp
        src/Server/Network/Client/BoostClient.hpp
        src/Server/Network/Client/AClient.hpp
        src/Common/Network.hpp
        src/Server/Server.hpp
        src/Server/Network/Network/ThreadPool.hpp
        src/Server/Network/Worker/ThreadSafeQueue.hpp
        src/Server/Network/Worker/Worker.hpp
        src/Server/Network/Room/RoomManager.hpp
        src/Server/Network/Room/Room.hpp
        src/Common/Network.cpp)

if (MSVC)
    set_target_properties(r-type_client PROPERTIES LINK_FLAGS /MACHINE:X64)
    set_target_properties(r-type_server PROPERTIES LINK_FLAGS /MACHINE:X64)
endif ()

install(TARGETS r-type_client DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS r-type_server DESTINATION ${PROJECT_SOURCE_DIR}/bin)

#############################################################
target_link_libraries(r-type_client ${CONAN_LIBS})
target_link_libraries(r-type_server ${CONAN_LIBS})
