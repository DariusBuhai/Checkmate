
# The minimum version of CMake required
cmake_minimum_required(VERSION 3.15)
# The project name
project(Checkmate)

add_executable(Checkmate main.cpp include/table.h include/piece.h include/draw.h src/draw.cpp src/table.cpp include/types.h include/templates.h)

# Linking SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
target_link_libraries(Checkmate sfml-graphics sfml-window sfml-system sfml-audio)

