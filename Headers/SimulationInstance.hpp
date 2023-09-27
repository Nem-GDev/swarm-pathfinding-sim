#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SwarmAgent.hpp"
#include "Colony.hpp"
#include "HeatMap.hpp"
#include "SwarmPreset.hpp"
// SwarmSim - github.com/Nem-GDev

namespace swt
{
    class SimulationInstance
    {
    private:
        SwarmConfig *preset;
        ThemeConfig *theme;
        sf::Vector2f spawnPosition;

    public:
        SimulationInstance(SwarmConfig &preset, ThemeConfig &theme);
        void RunSimulation();
    };
}
