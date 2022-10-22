cmake_minimum_required(VERSION 3.21)

project(Lab4
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_DEBUG ON)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS program_options system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(tcp_server "${CMAKE_CURRENT_SOURCE_DIR}/tcp_server.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/tcp_server.hpp")
target_include_directories(tcp_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(tcp_client "${CMAKE_CURRENT_SOURCE_DIR}/tcp_client.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/tcp_client.hpp")
target_include_directories(tcp_client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(udp_server "${CMAKE_CURRENT_SOURCE_DIR}/udp_server.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/udp_server.hpp")
target_include_directories(udp_server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(udp_client "${CMAKE_CURRENT_SOURCE_DIR}/udp_client.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/udp_client.hpp")
target_include_directories(udp_client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(application "${CMAKE_CURRENT_SOURCE_DIR}/application.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/application.hpp")
target_link_libraries(application PRIVATE Boost::program_options udp_server udp_client tcp_server tcp_client)
target_include_directories(application PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Lab4 "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(Lab4 PRIVATE application)
target_include_directories(Lab4 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
