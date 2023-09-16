#pragma once
#include <SFML\Graphics.hpp>

namespace swt
{
    class SwarmAgent : public sf::RectangleShape
    {
    private:
        sf::Vector2f nForward;
        void CalculateForward();
        void CheckScreenBounds(float screenX, float screenY);
        bool xOutOfBounds, yOutOfBounds;
        float screenWidth, screenHeight;

    public:
        SwarmAgent(sf::Color color, sf::Vector2f size, sf::Vector2f position, float screenX, float screenY);
        void PathfindTick();
        void MoveForward(float step);
    };
}