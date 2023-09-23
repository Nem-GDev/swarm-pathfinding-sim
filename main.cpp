#include <iostream>
#include <SFML/Graphics.hpp>
#include "SwarmAgent.hpp"
#include "Colony.hpp"
#include "HeatMap.hpp"
#include "SwarmPreset.hpp"
#include "SimulationInstance.hpp"
// SwarmSim V2.0 - github.com/Nem-GDev
//------------------------------------
//? CONTROLS:
//  H: Home (Place)
//  F: Food (Place)
//  W: Wall (Place)
//  C: Remove tile
//  S: Show paths
//  A: Show ants
////  D: Custom home path
////  R: Custom food path
//------------------------------------
int main(int, char **)
{
    std::string welcomeText;
    welcomeText = "\n-------------------------------------------\n";
    welcomeText += "Welcome to SwarmSim by github.com/Nem-GDev\n";
    welcomeText += "-------------------------------------------\n";
    welcomeText += "CONTROLS (Press key, then draw w/ LMB):----\n";
    welcomeText += "H: Home (Place)----------------------------\n";
    welcomeText += "F: Food (Place)----------------------------\n";
    welcomeText += "W: Wall (Place)----------------------------\n";
    welcomeText += "C: Remove tile-----------------------------\n";
    welcomeText += "S: Show paths------------------------------\n";
    welcomeText += "A: Show ants-------------------------------\n";
    welcomeText += "-------------------------------------------\n";
    int index = 0;
    bool getInput;
    swt::ThemeConfig *theme;
    swt::SwarmConfig *preset;

    while (true)
    {
        getInput = true;
        std::cout << welcomeText << std::endl;
        std::cout << "-Configure simulation-\n";
        std::cout << swt::SwarmPreset::GetThemeConfigList();
        std::cout << "\nPlease choose a theme: ";
        while (getInput)
        {
            std::cin >> index;
            getInput = swt::SwarmPreset::GetThemeConfig(index, theme);
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

        getInput = true;
        std::cout << swt::SwarmPreset::GetSwarmConfigList();
        std::cout << "\nPlease choose a preset: ";
        while (getInput)
        {
            std::cin >> index;
            getInput = swt::SwarmPreset::GetSwarmConfig(index, preset);
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

        std::cout << theme->CONFIG_NAME << std::endl;
        std::cout << preset->CONFIG_NAME << std::endl;

        swt::SimulationInstance instance(*preset, *theme);
        instance.RunSimulation();
    }

    return 0;
}
