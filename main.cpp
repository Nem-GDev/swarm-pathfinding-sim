#include <iostream>
#include <SFML\Graphics.hpp>
#include "SwarmAgent.hpp"
#include "Colony.hpp"
#include "Heatmap.hpp"

int screenWidth = 896;
int screenHeight = 896;
//? Currently tested Depletion*Move_Step:Max_Pheromone ratio ->
//? 5*200:6000
//? 2*200:3000
constexpr float
    OBEDIENCE = 600.f,
    //? Lower MaxPheromone = Higher Unity, Stability.
    //? Higher MaxPheromone = Higher mutation & new paths; Faster pathmap regeneration. Less Stability & Unity.
    MAX_PHEROMONE = 3000.f,
    //? Depletion >= Decay for reversed path disappearance
    //? (Depletion+Decay)/Max_Pheromone = Relative range
    PHEROMONE_DEPLETION = 2.f,
    PHEROMONE_DECAY = 2.f,
    MOVE_STEPS = 200.f,
    MOVEMENT_NOISE = 0.15f,
    COLONY_SIZE = 300.f;

int main(int, char **)
{
    //-------------------------
    //? CONTROLS:
    // H: Home (set)
    // F: Food (set)
    // S: Show paths
    // A: Show ants
    // D: Custom home path
    // R: Custom food path
    //-------------------------

    std::cout << "Hello, from swarm-pathfinding-sim!\n";
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                            "SFML Basics", sf::Style::Close | sf::Style::Titlebar);
    window.setKeyRepeatEnabled(false);
    sf::Vector2f spawnPos(screenWidth / 2, screenHeight / 2);
    sf::Vector2f screen(screenWidth, screenHeight);
    sf::Color backColor(230, 185, 80);

    //! Screen dimensions must be divisable by heatmap resolution!
    swt::HeatMap toFood(4, screen, sf::Color(140, 255, 0));
    toFood.UpdateVisualMap();
    swt::HeatMap toHome(4, screen, sf::Color(0, 140, 255));
    toHome.UpdateVisualMap();

    //! Screen dimensions must be divisable by heatmap resolution!
    swt::HeatMap homeSource(64, screen, sf::Color(0, 5, 140));
    homeSource.UpdateVisualMap();
    swt::HeatMap foodSource(64, screen, sf::Color(0, 80, 30));
    foodSource.UpdateVisualMap();

    swt::SwarmAgent ant1(sf::Color::Black, sf::Vector2f(10, 20), spawnPos, screen, OBEDIENCE);
    ant1.SetPheromoneMaps(toHome, toFood);
    ant1.SetSourceMaps(homeSource, foodSource, PHEROMONE_DEPLETION, MAX_PHEROMONE);
    ant1.SetMovementNoisePR(9, MOVEMENT_NOISE, 23);
    swt::Colony antColony(COLONY_SIZE, ant1);

    sf::Clock clock;
    float deltaTime;
    char paint;
    bool showMaps = true;
    bool showAnts = true;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event ev;

        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyReleased:
                if (ev.key.code == sf::Keyboard::S)
                    showMaps = !showMaps;
                else if (ev.key.code == sf::Keyboard::A)
                    showAnts = !showAnts;
            }
        }
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
                paint = 'h';
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                paint = 'f';
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                paint = 'd';
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                paint = 'r';
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i m = sf::Mouse::getPosition(window);
            // validate mouse position (within window bounds)
            if (m.x > 0 && m.y > 0 && m.x < screenWidth && m.y < screenHeight)
                switch (paint)
                {
                case 'h':
                    homeSource.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'f':
                    foodSource.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'd':
                    toHome.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;
                case 'r':
                    toFood.AddHeat(sf::Vector2f(m.x, m.y), 32000);
                    break;

                default:
                    break;
                }
        }

        {
            // TODO: Add pollrates to TickDown & UpdateVisualMap to improve performance
            toFood.TickDown(PHEROMONE_DECAY * MOVE_STEPS, deltaTime);
            toHome.TickDown(PHEROMONE_DECAY * MOVE_STEPS, deltaTime);
            antColony.TickMove(MOVE_STEPS, deltaTime);

            homeSource.UpdateVisualMap();
            foodSource.UpdateVisualMap();
            if (showMaps)
            {
                toFood.UpdateVisualMap();
                toHome.UpdateVisualMap();
            }
        }

        window.clear(backColor);
        {
            window.draw(homeSource);
            window.draw(foodSource);
            if (showMaps)
            {
                window.draw(toHome);
                window.draw(toFood);
            }
            if (showAnts)
                window.draw(antColony);
        }
        window.display();
    }
}
