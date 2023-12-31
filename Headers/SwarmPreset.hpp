#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>
// SwarmSim - github.com/Nem-GDev

namespace swt
{
    const std::out_of_range rgbOutOfBounds = std::out_of_range("RGB color must be between 0 and 255");
    struct ThemeConfig
    {
        std::string CONFIG_NAME;
        sf::Color BACK_COLOR;
        sf::Color SWARM_COLOR;

        sf::Color FOOD_PATH_COLOR;
        sf::Color FOOD_SOURCE_COLOR;
        sf::Color HOME_PATH_COLOR;
        sf::Color HOME_SOURCE_COLOR;
        sf::Color WALLS_COLOR;
    };
    //* NOTES:
    //*  Lower (screenwidth/swarmwidth) = Lower speed
    //*  Lower speed = Lower obedience =  Higher noise
    //*  Higher (MaxPheromone/Depletion) = Higher range
    //*  Higher MaxPheromone = Less Unity = Less clarity = Less accuracy= Faster update/refresh/regeneration
    struct SwarmConfig
    {
        std::string CONFIG_NAME;
        int VISUALMAP_POLLRATE;
        int VISUALMAP_ALPHACULLING;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        //! Screen dimensions must be divisable by heatmap resolution!
        int HEATMAP_SOURCE_RESOLUTION;
        int HEATMAP_PATH_RESOLUTION;
        int HEATMAP_WALLS_RESOLUTION;
        int SWARM_WIDTH;
        int SWARM_HEIGHT;
        int COLONY_SIZE;

        float SWARM_OBEDIENCE;
        //? Lower MaxPheromone = Higher Unity, Stability.
        //? Higher MaxPheromone = Higher mutation & new paths; Faster pathmap regeneration. Less Stability & Unity.
        float SWARM_MAX_PHEROMONE;
        //? Depletion >= Decay for reversed path disappearance
        //? (Depletion+Decay)/Max_Pheromone = Relative range
        float SWARM_PHEROMONE_DEPLETION;
        float SWARM_PHEROMONE_DECAY;
        float SWARM_MOVE_STEPS;
        float SWARM_NOISE;

        int SWARM_NOISE_POLLRATE;
        int SWARM_NOISE_DIRECTIONS;
    };
    class SwarmPreset
    {
    public:
        static std::string GetSwarmConfigList();
        static bool GetSwarmConfig(int index, SwarmConfig &preset);

        static std::string GetThemeConfigList();
        static bool GetThemeConfig(int index, ThemeConfig &theme);

        static ThemeConfig ParseTheme(nlohmann::json &json);
        static sf::Color ParseColor(nlohmann::json &json, std::string key);
        static std::vector<ThemeConfig> LoadThemes();

        static SwarmConfig ParsePreset(nlohmann::json &json);
        static std::vector<SwarmConfig> LoadPresets();
    };

    static ThemeConfig THEME_CONFIGS[] = {{
                                              "Biological",             // CONFIG_NAME
                                              sf::Color(189, 255, 248), // BACK_COLOR
                                              sf::Color(255, 255, 255), // SWARM_COLOR
                                              sf::Color(255, 0, 0),     // FOOD_PATH_COLOR
                                              sf::Color(255, 0, 0),     // FOOD_SOURCE_COLOR
                                              sf::Color(0, 255, 42),    // HOME_PATH_COLOR
                                              sf::Color(0, 255, 42),    // HOME_SOURCE_COLOR
                                              sf::Color::Black          // WALLS_COLOR;
                                          },
                                          {

                                              "Ants",                  // CONFIG_NAME
                                              sf::Color(230, 185, 80), // BACK_COLOR
                                              sf::Color::Black,        // SWARM_COLOR
                                              sf::Color(140, 255, 0),  // FOOD_PATH_COLOR
                                              sf::Color(0, 80, 30),    // FOOD_SOURCE_COLOR
                                              sf::Color(0, 140, 255),  // HOME_PATH_COLOR
                                              sf::Color(0, 5, 140),    // HOME_SOURCE_COLOR
                                              sf::Color::Black         // WALLS_COLOR;
                                          }

    };
    static SwarmConfig SWARM_CONFIGS[] = {
        {
            "PRESET_CUSTOM", // CONFIG_NAME
            1,               // VISUALMAP_POLLRATE;
            20,              // VISUALMAP_ALPHACULLING;
            896,             // SCREEN_WIDTH;
            896,             // SCREEN_HEIGHT;
            64,              // HEATMAP_SOURCE_RESOLUTION;
            4,               // HEATMAP_PATH_RESOLUTION;
            16,              // HEATMAP_WALLS_RESOLUTION;
            8,               // SWARM_WIDTH
            16,              // SWARM_HEIGHT;

            350,   // COLONY_SIZE;
            600,   // SWARM_OBEDIENCE;
            3000,  // SWARM_MAX_PHEROMONE;
            1.5f,  // SWARM_PHEROMONE_DEPLETION;
            15.f,  // SWARM_PHEROMONE_DECAY;
            200,   // SWARM_MOVE_STEPS;
            0.15f, // SWARM_NOISE;
            9,     // SWARM_NOISE_POLLRATE;
            23     // SWARM_NOISE_DIRECTIONS;
        },
        {
            "Small 1", // CONFIG_NAME
            1,         // VISUALMAP_POLLRATE;
            20,        // VISUALMAP_ALPHACULLING;
            896,       // SCREEN_WIDTH;
            896,       // SCREEN_HEIGHT;
            64,        // HEATMAP_SOURCE_RESOLUTION;
            4,         // HEATMAP_PATH_RESOLUTION;
            16,        // HEATMAP_WALLS_RESOLUTION;
            10,        // SWARM_WIDTH
            20,        // SWARM_HEIGHT;

            300,   // COLONY_SIZE;
            600,   // SWARM_OBEDIENCE;
            3000,  // SWARM_MAX_PHEROMONE;
            2,     // SWARM_PHEROMONE_DEPLETION;
            20,    // SWARM_PHEROMONE_DECAY;
            200,   // SWARM_MOVE_STEPS;
            0.15f, // SWARM_NOISE;
            9,     // SWARM_NOISE_POLLRATE;
            23     // SWARM_NOISE_DIRECTIONS;
        },
        {
            "Large 1", // CONFIG_NAME
            5,         // VISUALMAP_POLLRATE;
            20,        // VISUALMAP_ALPHACULLING;
            1024,      // SCREEN_WIDTH;
            1024,      // SCREEN_HEIGHT;
            64,        // HEATMAP_SOURCE_RESOLUTION;
            4,         // HEATMAP_PATH_RESOLUTION;
            16,        // HEATMAP_WALLS_RESOLUTION;
            8,         // SWARM_WIDTH
            16,        // SWARM_HEIGHT;

            900,   // COLONY_SIZE;
            600,   // SWARM_OBEDIENCE;h
            3600,  // SWARM_MAX_PHEROMONE;
            3,     // SWARM_PHEROMONE_DEPLETION;
            30,    // SWARM_PHEROMONE_DECAY;
            200,   // SWARM_MOVE_STEPS;
            0.15f, // SWARM_NOISE;
            9,     // SWARM_NOISE_POLLRATE;
            23     // SWARM_NOISE_DIRECTIONS;
        },
        {
            "Massive 1", // CONFIG_NAME
            15,          // VISUALMAP_POLLRATE;
            80,          // VISUALMAP_ALPHACULLING;
            1024,        // SCREEN_WIDTH;
            1024,        // SCREEN_HEIGHT;
            32,          // HEATMAP_SOURCE_RESOLUTION;
            2,           // HEATMAP_PATH_RESOLUTION;
            16,          // HEATMAP_WALLS_RESOLUTION;
            4,           // SWARM_WIDTH
            8,           // SWARM_HEIGHT;

            1200, // COLONY_SIZE;h
            400,  // SWARM_OBEDIENCE;h
            4800, // SWARM_MAX_PHEROMONE;
            4.f,  // SWARM_PHEROMONE_DEPLETION;
            40.f, // SWARM_PHEROMONE_DECAY;
            50,   // SWARM_MOVE_STEPS;
            0.3f, // SWARM_NOISE;
            9,    // SWARM_NOISE_POLLRATE;
            23    // SWARM_NOISE_DIRECTIONS;
        }};
}
