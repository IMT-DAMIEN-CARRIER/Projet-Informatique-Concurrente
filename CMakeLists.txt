project("projet-informatique-concurrente")
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 14)

add_executable(projet-informatique-concurrente-client client/client.c)
add_executable(projet-informatique-concurrente-server server/server.c)