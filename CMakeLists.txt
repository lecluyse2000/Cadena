cmake_minimum_required(VERSION 3.29)
project(Cadena)

add_compile_options(-Wall -Wextra)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Cadena)

target_sources(Cadena PRIVATE
    "src/main.cpp"
    "src/application.cpp"
    "src/passwordmanager.cpp"
    "src/hashtable.cpp"
)

target_include_directories(Cadena PUBLIC "src")
