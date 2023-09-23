#include <iostream>
#include <SFML/Graphics.hpp>
#include "SwarmAgent.hpp"
#include "Colony.hpp"
#include "HeatMap.hpp"
#include "SwarmPreset.hpp"
#include "ThemePreset.hpp"
// SwarmSim V2.0 - github.com/Nem-GDev

swt::SwarmPreset preset = swt::PRESET_1;
swt::ThemePreset theme = swt::THEME_2;

sf::Vector2f spawnPosition(preset.SCREEN_WIDTH / 2, preset.SCREEN_HEIGHT / 2);

//------------------------------------
//? CONTROLS:
//  H: Home (Place)
//  F: Food (Place)
//  W: Wall (Place)
//  C: Remove tile
//  S: Show paths
//  A: Show ants
//  D: Custom home path
//  R: Custom food path
//------------------------------------
int main(int, char **)
{
    std::cout << "Hello, from swarm-pathfinding-sim!\n";
    sf::Vector2f screen(preset.SCREEN_WIDTH, preset.SCREEN_HEIGHT);
    sf::RenderWindow window(sf::VideoMode(preset.SCREEN_WIDTH, preset.SCREEN_HEIGHT),
                            "SFML Basics", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    swt::HeatMap pathFood(swt::HeatMap::HeatMapType::FoodPath, preset, theme);
    swt::HeatMap pathHome(swt::HeatMap::HeatMapType::HomePath, preset, theme);
    swt::HeatMap homeSource(swt::HeatMap::HeatMapType::HomeSource, preset, theme);
    swt::HeatMap foodSource(swt::HeatMap::HeatMapType::FoodSource, preset, theme);
    swt::HeatMap walls(swt::HeatMap::HeatMapType::Walls, preset, theme);

    swt::SwarmAgent swarm0(spawnPosition, preset, theme);
    swarm0.SetPheromoneMaps(pathHome, pathFood);
    swarm0.SetSourceMaps(homeSource, foodSource, walls);
    swt::Colony antColony(preset, swarm0);

    sf::Clock clock;
    float deltaTime;
    char paint = ' ';
    bool showPathMaps = true;
    bool showAnts = true;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event ev;

        // Window management
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyReleased:
                if (ev.key.code == sf::Keyboard::S)
                    showPathMaps = !showPathMaps;
                else if (ev.key.code == sf::Keyboard::A)
                    showAnts = !showAnts;
            }
        }
        // Paint flags
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            paint = 'h';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            paint = 'f';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            paint = 'd';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            paint = 'r';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            paint = 'c';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            paint = 'w';

        // Painting w/ LMB
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i m = sf::Mouse::getPosition(window);
            // validate mouse position (within window bounds)
            if (m.x > 0 && m.y > 0 && m.x < preset.SCREEN_WIDTH && m.y < preset.SCREEN_HEIGHT)
                switch (paint)
                {
                case 'h':
                    homeSource.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'f':
                    foodSource.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'd':
                    pathHome.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'r':
                    pathFood.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'w':
                    walls.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'c':
                    foodSource.AddHeat(sf::Vector2f(m.x, m.y), -32000);
                    homeSource.AddHeat(sf::Vector2f(m.x, m.y), -32000);
                    walls.AddHeat(sf::Vector2f(m.x, m.y), -32000);
                    break;

                default:
                    break;
                }
        }

        // Ticking
        // TODO: Add pollrates to TickDown & UpdateVisualMap to improve performance
        pathFood.TickDown(preset.SWARM_PHEROMONE_DECAY * preset.SWARM_MOVE_STEPS, deltaTime);
        pathHome.TickDown(preset.SWARM_PHEROMONE_DECAY * preset.SWARM_MOVE_STEPS, deltaTime);
        antColony.TickMove(preset.SWARM_MOVE_STEPS, deltaTime);
        // Updating visual maps
        homeSource.UpdateVisualMap();
        foodSource.UpdateVisualMap();
        walls.UpdateVisualMap();
        if (showPathMaps)
        {
            pathFood.UpdateVisualMap();
            pathHome.UpdateVisualMap();
        }

        // Rendering objects
        window.clear(theme.BACK_COLOR);
        {
            if (showPathMaps)
            {
                window.draw(pathHome);
                window.draw(pathFood);
            }
            window.draw(walls);
            window.draw(homeSource);
            window.draw(foodSource);
            if (showAnts)
                window.draw(antColony);
        }
        window.display();
    }
}
