#include "SwarmPreset.hpp"
#include <sstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
// SwarmSim - github.com/Nem-GDev

using namespace swt;

std::string SwarmPreset::GetSwarmConfigList()
{
    std::stringstream ss;
    ss << "--------------------------\n";
    ss << "----- Base presets";
    int i;
    // skips first config (custom config)
    for (i = 1; i < sizeof(SWARM_CONFIGS) / sizeof(SwarmConfig); i++)
    {
        ss << "\n[ " << i + 1 << " ]: ";
        ss << SWARM_CONFIGS[i].CONFIG_NAME;
    }

    int j;
    ss << "\n----- Loaded json presets";
    std::vector<swt::SwarmConfig> presets = LoadPresets();
    for (j = 0; j < presets.size(); j++)
    {
        ss << "\n"
           << "[ " << i + j + 1 << " ]: ";
        ss << presets[j].CONFIG_NAME;
    }

    return ss.str();
}
bool SwarmPreset::GetSwarmConfig(int index, SwarmConfig &preset)
{
    int baseCount = sizeof(SWARM_CONFIGS) / sizeof(SwarmConfig);
    int loadedCount = LoadPresets().size();

    if (index - 1 < 0)
    {
        std::cout << "Please choose a valid preset number: ";
        return true;
    }
    else if (index - 1 < baseCount)
        preset = SWARM_CONFIGS[index - 1];

    else if (index - 1 < baseCount + loadedCount)
        preset = LoadPresets()[index - baseCount - 1];
    else
    {
        std::cout << "Please choose a valid preset number: ";
        return true;
    }

    return false;
}
std::string SwarmPreset::GetThemeConfigList()
{
    std::stringstream ss;
    ss << "--------------------------\n";
    ss << "----- Base themes";
    int i;
    for (i = 0; i < sizeof(THEME_CONFIGS) / sizeof(ThemeConfig); i++)
    {
        ss << "\n"
           << "[ " << i + 1 << " ]: ";
        ss << THEME_CONFIGS[i].CONFIG_NAME;
    }

    int j;
    ss << "\n----- Loaded json themes";
    std::vector<swt::ThemeConfig> themes = LoadThemes();
    for (j = 0; j < themes.size(); j++)
    {
        ss << "\n"
           << "[ " << i + j + 1 << " ]: ";
        ss << themes[j].CONFIG_NAME;
    }
    
    return ss.str();
}
bool SwarmPreset::GetThemeConfig(int index, ThemeConfig &theme)
{
    int baseCount = sizeof(THEME_CONFIGS) / sizeof(ThemeConfig);
    int loadedCount = LoadThemes().size();

    if (index - 1 < 0)
    {
        std::cout << "Please choose a valid theme number: ";
        return true;
    }
    else if (index - 1 < baseCount)
        theme = THEME_CONFIGS[index - 1];

    else if (index - 1 < baseCount + loadedCount)
        theme = LoadThemes()[index - baseCount - 1];
    else
    {
        std::cout << "Please choose a valid theme number: ";
        return true;
    }

    return false;
}

ThemeConfig SwarmPreset::ParseTheme(nlohmann::json &json)
{
    std::string config_name = json["config_name"].template get<std::string>();
    sf::Color back_color = ParseColor(json, "back_color");
    sf::Color swarm_color = ParseColor(json, "swarm_color");
    sf::Color food_path_color = ParseColor(json, "food_path_color");
    sf::Color food_source_color = ParseColor(json, "food_source_color");
    sf::Color home_path_color = ParseColor(json, "home_path_color");
    sf::Color home_source_color = ParseColor(json, "home_source_color");
    sf::Color walls_color = ParseColor(json, "walls_color");

    return {
        config_name,
        back_color,
        swarm_color,
        food_path_color,
        food_source_color,
        home_path_color,
        home_source_color,
        walls_color};
}

sf::Color SwarmPreset::ParseColor(nlohmann::json &json, std::string key)
{
    int r = json[key]["r"].template get<int>();
    int g = json[key]["g"].template get<int>();
    int b = json[key]["b"].template get<int>();

    if (r > 255 || r < 0 ||
        g > 255 || g < 0 ||
        b > 255 || b < 0)
        throw rgbOutOfBounds;
    else
        return sf::Color(r, g, b);
}

std::vector<ThemeConfig> SwarmPreset::LoadThemes()
{
    std::vector<std::filesystem::path> themePaths;
    std::vector<swt::ThemeConfig> themes;

    // get paths to theme jsons
    try
    {
        for (const auto &file : std::filesystem::directory_iterator(".\\Themes"))
        {
            if (file.path().extension() == ".json")
            {
                themePaths.push_back(file.path());
            }
        }
    }
    catch (const std::exception &e)
    {
        // catching invalid/non existent folder
        std::cerr << e.what() << '\n';
        return themes;
    }

    // parse json themes and populate vector
    for (const auto path : themePaths)
    {
        try
        {
            std::fstream f(path);
            auto json = nlohmann::json::parse(f);
            themes.push_back(ParseTheme(json));
            f.close();
        }
        catch (const std::exception &e)
        {
            // catching ivalid theme json
            std::cerr << e.what() << '\n';
        }
    }
    return themes;
}

SwarmConfig SwarmPreset::ParsePreset(nlohmann::json &json)
{
    std::string config_name = json["config_name"].template get<std::string>();
    int visualmap_pollrate = json["visualmap_pollrate"].template get<int>();
    int visualmap_alphaculling = json["visualmap_alphaculling"].template get<int>();
    int screen_width = json["screen_width"].template get<int>();
    int screen_height = json["screen_height"].template get<int>();
    int heatmap_source_resolution = json["heatmap_source_resolution"].template get<int>();
    int heatmap_path_resolution = json["heatmap_path_resolution"].template get<int>();
    int heatmap_walls_resolution = json["heatmap_walls_resolution"].template get<int>();
    int swarm_width = json["swarm_width"].template get<int>();
    int swarm_height = json["swarm_height"].template get<int>();
    int colony_size = json["colony_size"].template get<int>();

    float swarm_obedience = json["swarm_obedience"].template get<float>();
    float swarm_max_pheromone = json["swarm_max_pheromone"].template get<float>();
    float swarm_pheromone_depletion = json["swarm_pheromone_depletion"].template get<float>();
    float swarm_pheromone_decay = json["swarm_pheromone_decay"].template get<float>();
    float swarm_move_steps = json["swarm_move_steps"].template get<float>();
    float swarm_noise = json["swarm_noise"].template get<float>();

    int swarm_noise_pollrate = json["swarm_noise_pollrate"].template get<int>();
    int swarm_noise_directions = json["swarm_noise_directions"].template get<int>();

    return {
        config_name,
        visualmap_pollrate,
        visualmap_alphaculling,
        screen_width,
        screen_height,
        heatmap_source_resolution,
        heatmap_path_resolution,
        heatmap_walls_resolution,
        swarm_width,
        swarm_height,
        colony_size,

        swarm_obedience,
        swarm_max_pheromone,
        swarm_pheromone_depletion,
        swarm_pheromone_decay,
        swarm_move_steps,
        swarm_noise,

        swarm_noise_pollrate,
        swarm_noise_directions};
}

std::vector<SwarmConfig> SwarmPreset::LoadPresets()
{
    std::vector<std::filesystem::path> presetPaths;
    std::vector<swt::SwarmConfig> presets;

    // get paths to theme jsons
    try
    {
        for (const auto &file : std::filesystem::directory_iterator(".\\Presets"))
        {
            if (file.path().extension() == ".json")
            {
                presetPaths.push_back(file.path());
            }
        }
    }
    catch (const std::exception &e)
    {
        // catching invalid/non existent folder
        std::cerr << e.what() << '\n';
        return presets;
    }

    // parse json themes and populate vector
    for (const auto path : presetPaths)
    {
        try
        {
            std::fstream f(path);
            auto json = nlohmann::json::parse(f);
            presets.push_back(ParsePreset(json));
            f.close();
        }
        catch (const std::exception &e)
        {
            // catching ivalid theme json
            std::cerr << e.what() << '\n';
        }
    }
    return presets;
}