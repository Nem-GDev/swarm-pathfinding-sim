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
    window.setFramerateLimit(90);

    sf::Vector2f pos(screenWidth / 2, screenHeight / 2);
    swt::SwarmAgent ant1(sf::Color::Cyan, sf::Vector2f(5, 12), pos, screenWidth, screenHeight);

    swt::Colony antColony(500, ant1);
    // ant1.wallBounceCDms = 300;
    // ant1.rotate(-45);
    // std::cout << sizeof(unsigned short) << std::endl;

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
        //
        // ant1.PathfindTick();
        // ant1.MoveForward(1);
        antColony.TickColonyMove(3);

        window.clear(backColor);
        // rendering
        // window.draw(ant1);
        // antColony.DrawColony(window);
        window.draw(antColony);

        window.display();

        // testing repo
    }
}
