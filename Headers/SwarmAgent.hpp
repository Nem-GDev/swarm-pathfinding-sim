#pragma once
#include <SFML/Graphics.hpp>
#include "HeatMap.hpp"
#include "SwarmPreset.hpp"
// SwarmSim - github.com/Nem-GDev

namespace swt
{
    class SwarmAgent : public sf::RectangleShape
    {
    private:
        sf::Vector2f nForward;
        sf::Transformable lAntenna;
        sf::Transformable rAntenna;
        bool xOutOfBounds, yOutOfBounds, hasMovementNoise = false;
        float screenWidth, screenHeight, movementNoiseStrength, obedience, currentPheromoneRange, pheromoneDepletion;
        float maxPheromone = 1500;
        double pherDeduct;
        int movementNoisePR = 0, currentMovementNoisePoll = 0, movementNoiseDirections = 0;
        HeatMap *toHome, *toFood, *homeSource, *foodSource, *walls;
        enum Pheromone
        {
            DepartingHome = 1,
            FoundFood = 2,
            Lost = 3,
        };
        Pheromone currentPheromone = Pheromone::Lost;
        void CalculateForward();
        void CheckScreenBounds(float screenX, float screenY);
        void AddMovementNoise(float steps, float dt);
        void FollowMap(float strength, float dt);
        bool ScanHeatMaps();
        void EmitPheromone(float steps, float dt);
        void ReflectOffWall(char sideHit);

    public:
        int seed;
        sf::RectangleShape DebugRAntenna();
        sf::RectangleShape DebugLAntenna();
        SwarmAgent(sf::Vector2f position, swt::SwarmConfig &preset, swt::ThemeConfig &theme);
        void MoveForward(float step, float dt);
        void SetMovementNoisePR(int pollRate, float strength, int directions);
        void SetPheromoneMaps(HeatMap &toHome, HeatMap &toFood);
        void SetSourceMaps(HeatMap &homeSource, HeatMap &foodSource, HeatMap &walls);
    };

}