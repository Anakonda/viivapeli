cmake_minimum_required(VERSION 3.1)

project(viivapeli CXX)

set (CMAKE_CXX_STANDARD 14)

add_executable(viivapeli WIN32 src/main.cpp src/renderer.cpp src/coordinates.cpp src/line.cpp)
target_link_libraries(viivapeli allegro allegro_font allegro_ttf allegro_primitives)
