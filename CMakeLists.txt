cmake_minimum_required(VERSION 3.17)
project(tcp_chat)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

link_libraries(ws2_32 wsock32)

add_executable(server server.cpp)

add_executable(client client.cpp)