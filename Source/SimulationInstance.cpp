#include <iostream>
#include <SFML/Graphics.hpp>
#include "SwarmAgent.hpp"
#include "Colony.hpp"
#include "HeatMap.hpp"
#include "SwarmPreset.hpp"
#include "SimulationInstance.hpp"
// SwarmSim V2.0 - github.com/Nem-GDev
using namespace swt;

SimulationInstance::SimulationInstance(SwarmConfig &preset, ThemeConfig &theme)
{
    this->preset = &preset;
    this->theme = &theme;
    this->spawnPosition = sf::Vector2f(preset.SCREEN_WIDTH / 2, preset.SCREEN_HEIGHT / 2);
}

void SimulationInstance::RunSimulation()
{

    sf::Vector2f screen(preset->SCREEN_WIDTH, preset->SCREEN_HEIGHT);
    sf::RenderWindow window(sf::VideoMode(preset->SCREEN_WIDTH, preset->SCREEN_HEIGHT),
                            "SwarmSim Instance", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    HeatMap pathFood(HeatMap::HeatMapType::FoodPath, *preset, *theme);
    HeatMap pathHome(HeatMap::HeatMapType::HomePath, *preset, *theme);
    HeatMap homeSource(HeatMap::HeatMapType::HomeSource, *preset, *theme);
    HeatMap foodSource(HeatMap::HeatMapType::FoodSource, *preset, *theme);
    HeatMap walls(HeatMap::HeatMapType::Walls, *preset, *theme);

    swt::SwarmAgent swarm0(spawnPosition, *preset, *theme);
    swarm0.SetPheromoneMaps(pathHome, pathFood);
    swarm0.SetSourceMaps(homeSource, foodSource, walls);
    swt::Colony antColony(*preset, swarm0);

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
        // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        //     paint = 'd';
        // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        //     paint = 'r';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            paint = 'c';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            paint = 'w';

        // Painting w/ LMB
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i m = sf::Mouse::getPosition(window);
            // validate mouse position (within window bounds)
            if (m.x > 0 && m.y > 0 && m.x < preset->SCREEN_WIDTH && m.y < preset->SCREEN_HEIGHT)
                switch (paint)
                {
                case 'h':
                    homeSource.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'f':
                    foodSource.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                // case 'd':
                //     pathHome.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                //     break;
                // case 'r':
                //     pathFood.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                //     break;
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
        pathFood.TickDown(preset->SWARM_PHEROMONE_DECAY * preset->SWARM_MOVE_STEPS, deltaTime);
        pathHome.TickDown(preset->SWARM_PHEROMONE_DECAY * preset->SWARM_MOVE_STEPS, deltaTime);
        antColony.TickMove(preset->SWARM_MOVE_STEPS, deltaTime);
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
        window.clear(theme->BACK_COLOR);
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