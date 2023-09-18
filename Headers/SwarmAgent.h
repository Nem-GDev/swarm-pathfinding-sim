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
        void AddMovementNoise();
        bool xOutOfBounds, yOutOfBounds, hasMovementNoise = false;
        float screenWidth, screenHeight, movementNoiseStrength;
        int movementNoisePR = 0, currentMovementNoisePoll = 0, movementNoiseDirections = 0;

    public:
        SwarmAgent(sf::Color color, sf::Vector2f size, sf::Vector2f position, float screenX, float screenY);
        void PathfindTick();
        void MoveForward(float step);
        void SetMovementNoisePR(int pollRate, float strength, int directions);
        int seed;
    };

}