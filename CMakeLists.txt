cmake_minimum_required(VERSION 3.7.1)

project(tic-tac-toe)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )	#For semantic support in Vim

message(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

add_executable(server server.c game.c)
add_executable(client client.c)

