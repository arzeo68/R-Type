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

add_executable(r-type_client
    Client/main.cpp
    Client/src/window/Window.cpp
    Client/include/window/Window.hpp
    Client/src/window/AWindow.cpp
    Client/include/window/AWindow.hpp
    Client/include/typeEncapsulation.hpp
    Client/include/RenderTarget/IRenderTarget.hpp
    Client/include/RenderTarget/ARenderTarget.hpp
    Client/src/RenderTarget/RenderTarget.cpp
    Client/include/RenderTarget/RenderTarget.hpp
    Client/include/SceneManager/SceneManager.hpp
    Client/src/SceneManager/SceneManager.cpp
    Client/include/ObserverPattern/Subject.hpp
    Client/include/EventManager/EventManager.hpp
    Client/include/EventManager/SFMLEvents.hpp
    Client/src/EventManager/EventManager.cpp
    Client/src/Application/Application.cpp
    Client/include/Application/Application.hpp
    Client/Components/Network.hpp
    Client/include/unique_id.hpp
    Client/ClientNetwork/ISocket.hpp
    Client/ClientNetwork/ASocket.hpp
    Client/ClientNetwork/TcpNetwork.cpp
    Client/ClientNetwork/TcpNetwork.hpp
    Client/ClientNetwork/UdpNetwork.cpp
    Client/ClientNetwork/UdpNetwork.hpp
    Common/Network.hpp)
add_executable(r-type_server
        Server/Network/Network/INetwork.hpp
        Server/Network/Socket/ISocket.hpp
        Server/Network/Network/Router.hpp
        Server/Network/Network/BoostNetwork.cpp
        Server/Network/Network/BoostNetwork.hpp
        Server/Network/Network/ANetwork.hpp
        Server/Main.cpp
        Common/Log.hpp Common/Log.cpp
        Server/Network/Socket/TCPBoostSocket.cpp
        Server/Network/Socket/TCPBoostSocket.hpp
        Server/Network/Socket/UDPBoostSocket.cpp
        Server/Network/Socket/UDPBoostSocket.hpp
        Server/Network/Client/BoostClient.cpp
        Server/Network/Client/BoostClient.hpp
        Server/Network/Client/AClient.hpp
        Common/Network.hpp
        Server/Server.hpp
        Server/Network/Network/ThreadPool.hpp
        Server/Network/Worker/ThreadSafeQueue.hpp
        Server/Network/Worker/Worker.hpp
        Server/Network/Room/RoomManager.hpp
        Server/Network/Room/Room.hpp
        Common/Network.cpp)

if (MSVC)
    set_target_properties(r-type_client PROPERTIES LINK_FLAGS /MACHINE:X64)
    set_target_properties(r-type_server PROPERTIES LINK_FLAGS /MACHINE:X64)
endif ()

install(TARGETS r-type_client DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS r-type_server DESTINATION ${PROJECT_SOURCE_DIR}/bin)

#############################################################
target_link_libraries(r-type_client ${CONAN_LIBS})
target_link_libraries(r-type_server ${CONAN_LIBS})
