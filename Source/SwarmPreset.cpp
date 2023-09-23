#include "SwarmPreset.hpp"
#include <sstream>
#include <iostream>

using namespace swt;

std::string SwarmPreset::GetSwarmConfigList()
{
    std::stringstream ss;
    ss << "--------------------------\n";
    ss << "Available presets:";
    // skips first config (custom config)
    for (int i = 1; i < sizeof(SWARM_CONFIGS) / sizeof(SwarmConfig); i++)
    {
        ss << "\n[ " << i + 1 << " ]: ";
        ss << SWARM_CONFIGS[i].CONFIG_NAME;
    }
    return ss.str();
}
bool SwarmPreset::GetSwarmConfig(int index, SwarmConfig *&preset)
{
    if (index - 1 < 0 || index > sizeof(SWARM_CONFIGS) / sizeof(SwarmConfig))
    {
        std::cout << "Please choose a valid preset number: ";
        return true;
    }
    else
        preset = &SWARM_CONFIGS[index - 1];
    return false;
}
std::string SwarmPreset::GetThemeConfigList()
{
    std::stringstream ss;
    ss << "--------------------------\n";
    ss << "Available themes:";
    // skips first config (custom config)
    for (int i = 0; i < sizeof(THEME_CONFIGS) / sizeof(ThemeConfig); i++)
    {
        ss << "\n"
           << "[ " << i + 1 << " ]: ";
        ss << THEME_CONFIGS[i].CONFIG_NAME;
    }
    return ss.str();
}
bool SwarmPreset::GetThemeConfig(int index, ThemeConfig *&theme)
{
    if (index - 1 < 0 || index > sizeof(THEME_CONFIGS) / sizeof(ThemeConfig))
    {
        std::cout << "Please choose a valid theme number: ";
        return true;
    }
    else
        theme = &THEME_CONFIGS[index - 1];
    return false;
}
