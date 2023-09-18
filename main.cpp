#include <iostream>
#include <SFML\Graphics.hpp>
#include "SwarmAgent.h"
#include "Colony.h"

int screenWidth = 768;
int screenHeight = 768;
sf::Color backColor(230, 185, 80);

int main(int, char **)
{
    std::cout << "Hello, from swarm-pathfinding-sim!\n";
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                            "SFML Basics", sf::Style::Close | sf::Style::Titlebar);
    // window.setFramerateLimit(90);
    sf::Vector2f pos(screenWidth / 2, screenHeight / 2);

    swt::SwarmAgent ant1(sf::Color(133, 66, 0), sf::Vector2f(3, 6), pos, screenWidth, screenHeight);
    ant1.SetMovementNoisePR(4, 0.05f, 113);
    swt::Colony antColony(4000, ant1);

    while (window.isOpen())
    {
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
            // ant1.rotate(-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            // ant1.rotate(1);
        }
        antColony.TickMove(2.0f);
        // antColony.TickMoveThreaded(2.0f, 4);

        window.clear(backColor);

        // antColony.DrawColony(window);
        window.draw(antColony);
        window.display();

        // testing repo
    }
}
