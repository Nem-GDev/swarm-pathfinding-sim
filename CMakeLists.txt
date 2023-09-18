cmake_minimum_required(VERSION 3.0.0)
project(swarm-pathfinding-sim VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()
add_executable(swarm-pathfinding-sim main.cpp Source/HeatMap.cpp Headers/HeatMap.hpp Source/SwarmAgent.cpp Headers/SwarmAgent.h
    Source/Colony.cpp Headers/Colony.h)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(swarm-pathfinding-sim PRIVATE sfml-system sfml-window sfml-graphics)
target_include_directories(swarm-pathfinding-sim PRIVATE Headers)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
