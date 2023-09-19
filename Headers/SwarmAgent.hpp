#pragma once
#include <SFML\Graphics.hpp>
#include "HeatMap.hpp"

namespace swt
{
    class SwarmAgent : public sf::RectangleShape
    {
    private:
        sf::Vector2f nForward;
        void CalculateForward();
        void CheckScreenBounds(float screenX, float screenY);
        void AddMovementNoise(float dt);
        void FollowHeat(float strength, float dt);
        sf::Transformable lAntenna;
        sf::Transformable rAntenna;
        bool xOutOfBounds, yOutOfBounds, hasMovementNoise = false;
        float screenWidth, screenHeight, movementNoiseStrength, obedience;
        int movementNoisePR = 0, currentMovementNoisePoll = 0, movementNoiseDirections = 0;
        HeatMap *hm1;

    public:
        sf::RectangleShape DebugRAntenna();
        sf::RectangleShape DebugLAntenna();
        SwarmAgent(sf::Color color, sf::Vector2f size, sf::Vector2f position, sf::Vector2f screenSize, HeatMap &hm, float obedience);
        void PathfindTick();
        void MoveForward(float step, float dt);
        void SetMovementNoisePR(int pollRate, float strength, int directions);
        int seed;
    };

}