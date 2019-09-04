cmake_minimum_required(VERSION 3.7.1)

project(tic-tac-toe)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )	#For semantic support in Vim
set(SOURCE_CLIENT src/client.c)
set(SOURCE_SERVER src/game.c src/server.c)
set(EXECUTABLE_OUTPUT_PATH "bin")

message(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

add_executable(server ${SOURCE_SERVER})
add_executable(client ${SOURCE_CLIENT})

