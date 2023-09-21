#pragma once
#include <SFML\Graphics.hpp>

namespace swt
{
    struct ThemePreset
    {
        const sf::Color BACK_COLOR;
        const sf::Color SWARM_COLOR;

        const sf::Color FOOD_PATH_COLOR;
        const sf::Color FOOD_SOURCE_COLOR;
        const sf::Color HOME_PATH_COLOR;
        const sf::Color HOME_SOURCE_COLOR;
    };

    static ThemePreset THEME_1{
        sf::Color(230, 185, 80), // BACK_COLOR
        sf::Color::Black,        // SWARM_COLOR
        sf::Color(140, 255, 0),  // FOOD_PATH_COLOR
        sf::Color(0, 80, 30),    // FOOD_SOURCE_COLOR
        sf::Color(0, 140, 255),  // HOME_PATH_COLOR
        sf::Color(0, 5, 140)     // HOME_SOURCE_COLOR

    };
    static ThemePreset THEME_2{
        sf::Color(189, 255, 248), // BACK_COLOR
        sf::Color(255, 255, 255), // SWARM_COLOR
        sf::Color(255, 0, 0),     // FOOD_PATH_COLOR
        sf::Color(255, 0, 0),     // FOOD_SOURCE_COLOR
        sf::Color(0, 255, 42),    // HOME_PATH_COLOR
        sf::Color(0, 255, 42)     // HOME_SOURCE_COLOR

    };
}