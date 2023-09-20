#include <iostream>
#include <SFML\Graphics.hpp>
#include "SwarmAgent.hpp"
#include "Colony.hpp"
#include "Heatmap.hpp"

int screenWidth = 896;
int screenHeight = 896;
sf::Color backColor(230, 185, 80);

constexpr float
    OBEDIENCE = 800.f,
    //? Depletion >= Decay for reversed path disappearance
    PHEROMONE_DEPLETION = 10.f,
    PHEROMONE_DECAY = 10.f,
    /////? Speed effects range AND smoothens path disappearance
    MOVE_STEPS = 200.f,
    MOVEMENT_NOISE = 0.2f,
    COLONY_SIZE = 300.f;

int main(int, char **)
{
    std::cout << "Hello, from swarm-pathfinding-sim!\n";
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                            "SFML Basics", sf::Style::Close | sf::Style::Titlebar);
    window.setKeyRepeatEnabled(false);
    // window.setFramerateLimit(90);
    sf::Vector2f pos(screenWidth / 2, screenHeight / 2);
    sf::Vector2f screen(screenWidth, screenHeight);

    swt::HeatMap toFood(4, screen, sf::Color(140, 255, 0));
    toFood.UpdateVisualMap();
    swt::HeatMap toHome(4, screen, sf::Color(0, 140, 255));
    toHome.UpdateVisualMap();

    swt::HeatMap homeSource(96, screen, sf::Color(0, 5, 140));
    homeSource.UpdateVisualMap();
    swt::HeatMap foodSource(96, screen, sf::Color(0, 80, 30));
    // toFood.AddHeat(sf::Vector2f(300, 300), 20000);
    foodSource.UpdateVisualMap();

    swt::SwarmAgent ant1(sf::Color::Black, sf::Vector2f(10, 20), pos, screen, OBEDIENCE);
    ant1.SetPheromoneMaps(toHome, toFood);
    ant1.SetSourceMaps(homeSource, foodSource, PHEROMONE_DEPLETION);
    ant1.SetMovementNoisePR(9, MOVEMENT_NOISE, 23);
    swt::Colony antColony(COLONY_SIZE, ant1);

    // ? Quad clockwise vertex pattern
    // arr[0].position = sf::Vector2f(240, 240);
    // arr[1].position = sf::Vector2f(240, 340);
    // arr[2].position = sf::Vector2f(340, 340);
    // arr[3].position = sf::Vector2f(340, 240);
    sf::Clock clock;
    float deltaTime;
    char paint;
    bool showMaps = false;
    bool showAnts = false;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        // std::cout << deltaTime << std::endl;
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
            // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            //     showMaps = !showMaps;
            // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            //     showAnts = !showAnts;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            ant1.rotate(-0.05);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            ant1.rotate(0.05);
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

        // TODO: Add pollrates to TickDown & UpdateVisualMap to improve performance
        toFood.TickDown(PHEROMONE_DECAY * MOVE_STEPS, deltaTime);
        toHome.TickDown(PHEROMONE_DECAY * MOVE_STEPS, deltaTime);
        homeSource.UpdateVisualMap();
        foodSource.UpdateVisualMap();
        // std::cout << toHome.GetHeat(sf::Vector2f(500, 500)) << std::endl;

        if (showMaps)
        {
            /* code */
            toFood.UpdateVisualMap();
            toHome.UpdateVisualMap();
        }

        //   hm.UpdateVisualMap();
        //   std::cout << "Heat at target: " << hm.GetHeat(20, 60) << std::endl;
        //   antColony.TickMoveThreaded(2.0f, 4);
        antColony.TickMove(MOVE_STEPS, deltaTime);
        // ant1.MoveForward(0.05f);

        window.clear(backColor);
        // window.draw(ant1);
        // window.draw(ant1.DebugRAntenna());
        // window.draw(ant1.DebugLAntenna());
        // window.draw(toHome);
        // window.draw(toFood);
        window.draw(homeSource);
        window.draw(foodSource);
        if (showMaps)
        {
            window.draw(toHome);
            window.draw(toFood);
        }
        if (showAnts)
            window.draw(antColony);
        //    window.draw(hm);
        //    window.draw(arr);

        window.display();
    }
}
