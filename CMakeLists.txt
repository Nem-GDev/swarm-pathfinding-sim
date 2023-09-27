cmake_minimum_required(VERSION 3.20.0)
project(swarm-pathfinding-sim VERSION 3.0 LANGUAGES CXX)

add_executable(swarm-pathfinding-sim main.cpp Source/HeatMap.cpp Headers/HeatMap.hpp Source/SwarmAgent.cpp Headers/SwarmAgent.hpp
    Source/Colony.cpp Headers/Colony.hpp Headers/SwarmPreset.hpp Source/SimulationInstance.cpp Source/SwarmPreset.cpp
    Headers/SimulationInstance.hpp)
set_property(TARGET swarm-pathfinding-sim PROPERTY CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(swarm-pathfinding-sim PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(swarm-pathfinding-sim PRIVATE sfml-system sfml-window sfml-graphics)
target_include_directories(swarm-pathfinding-sim PRIVATE Headers)
