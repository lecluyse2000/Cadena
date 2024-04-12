cmake_minimum_required(VERSION 3.29)
project(Cadena)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

include_directories("src")

add_executable(Cadena ${SOURCES})
