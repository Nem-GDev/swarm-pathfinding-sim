#include <iostream>
#include <SFML\Graphics.hpp>
#include "SwarmAgent.hpp"
#include "Colony.hpp"
#include "Heatmap.hpp"

int screenWidth = 912;
int screenHeight = 912;
sf::Color backColor(230, 185, 80);

int main(int, char **)
{
    std::cout << "Hello, from swarm-pathfinding-sim!\n";
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                            "SFML Basics", sf::Style::Close | sf::Style::Titlebar);
    // window.setFramerateLimit(90);
    sf::Vector2f pos(screenWidth / 2, screenHeight / 2);

    swt::HeatMap hm(2, screenWidth, screenHeight, sf::Color(0, 140, 255));
    hm.UpdateVisualMap();
    // hm.AddHeat(pos, 300);

    swt::SwarmAgent ant1(sf::Color(133, 66, 0), sf::Vector2f(4, 8), pos, sf::Vector2f(screenWidth, screenHeight), hm, 800.f);
    ant1.SetMovementNoisePR(7, 40.0f, 13);
    swt::Colony antColony(300, ant1, hm);

    // sf::VertexArray arr;
    // arr.setPrimitiveType(sf::Quads);
    // arr.resize(32);
    // ? Quad clockwise vertex pattern
    // arr[0].position = sf::Vector2f(240, 240);
    // arr[1].position = sf::Vector2f(240, 340);
    // arr[2].position = sf::Vector2f(340, 340);
    // arr[3].position = sf::Vector2f(340, 240);
    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        // std::cout << deltaTime << std::endl;
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
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
            if (m.x > 0 && m.y > 0)
                if (m.x < screenWidth && m.y < screenHeight)
                    hm.AddHeat(sf::Vector2f(m.x, m.y), 6000);
        }

        // TODO: Add pollrates to TickDown & UpdateVisualMap to improve performance
        hm.TickDown(deltaTime);
        // hm.UpdateVisualMap();
        //   std::cout << "Heat at target: " << hm.GetHeat(20, 60) << std::endl;
        //   antColony.TickMoveThreaded(2.0f, 4);
        antColony.TickMove(50.0f, deltaTime);
        // ant1.MoveForward(0.05f);

        window.clear(backColor);
        // window.draw(ant1);
        // window.draw(ant1.DebugRAntenna());
        // window.draw(ant1.DebugLAntenna());
        window.draw(hm);
        window.draw(antColony);
        //   window.draw(hm);
        //   window.draw(arr);

        window.display();
    }
}
