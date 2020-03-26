cmake_minimum_required(VERSION 3.15)
project(Checkmate)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "SFML/include")
set(SFML_LIBRARY_DIR "SFML/build/lib")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(Checkmate main.cpp)

target_link_libraries (Checkmate sfml-graphics sfml-window sfml-system)