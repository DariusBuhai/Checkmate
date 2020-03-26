# The minimum version of CMake required
cmake_minimum_required(VERSION 3.15)
# The project name
project(Checkmate)
# The C++ standard version. Can be 98 11 14 or 17

add_executable(Checkmate main.cpp)

set(SFML_INCLUDE_DIR "SFML/include")
set(SFML_LIBRARY_DIR "SFML/build/lib")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

target_link_libraries (Checkmate sfml-graphics sfml-window sfml-system)