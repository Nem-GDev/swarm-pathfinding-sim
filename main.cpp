#include <iostream>
#include <SFML\Graphics.hpp>
#include "SwarmAgent.h"
#include "Colony.h"
#include "Heatmap.hpp"

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
    ant1.SetMovementNoisePR(7, 1.0f, 13);
    swt::Colony antColony(4000, ant1);

    swt::HeatMap hm(16, screenWidth, screenHeight, sf::Color(0, 140, 255));
    hm.AddHeat(screenWidth / 2, screenHeight / 2, 300);

    // sf::VertexArray arr;
    // arr.setPrimitiveType(sf::Quads);
    // arr.resize(32);
    // ? Quad clockwise vertex pattern
    // arr[0].position = sf::Vector2f(240, 240);
    // arr[1].position = sf::Vector2f(240, 340);
    // arr[2].position = sf::Vector2f(340, 340);
    // arr[3].position = sf::Vector2f(340, 240);

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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i m = sf::Mouse::getPosition(window);
            // std::cout << "X: " << m.x << "| Y: " << m.y << std::endl;
            if (m.x > 0 && m.y > 0)
                if (m.x < screenWidth && m.y < screenHeight)
                    hm.AddHeat(m.x, m.y, 90);
        }

        // TODO: Add pollrates to TickDown & UpdateVisualMap to improve performance
        hm.TickDown();
        hm.UpdateVisualMap();
        // std::cout << "Heat at target: " << hm.GetHeat(20, 60) << std::endl;
        // antColony.TickMoveThreaded(2.0f, 4);
        antColony.TickMove(1.0f);

        window.clear(backColor);
        window.draw(hm);
        window.draw(antColony);
        // window.draw(hm);
        // window.draw(arr);

        window.display();
    }
}
