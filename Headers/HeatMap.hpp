#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "SwarmPreset.hpp"
// SwarmSim - github.com/Nem-GDev

namespace swt
{
    class HeatMap : public sf::Drawable
    {
    private:
        short mapPrecision, screenWidth, screenHeight;
        short mapWidth, mapHeight, visualMapWidth, visualMapHeight, mapWRange, mapHRange;
        int mapSize, visualMapSize, currentVisualPoll = 0, maxVisualPoll = 1, visualAlphaCulling = 0;
        double alphaConversion;

        std::vector<std::vector<short>> map;
        sf::VertexArray visualMap;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void InitVisualMap();

    public:
        enum HeatMapType
        {
            FoodPath,
            FoodSource,
            HomePath,
            HomeSource,
            Walls
        };
        HeatMapType hmType;
        sf::Color baseHeatColor;
        HeatMap(int resolution, sf::Vector2f screen, sf::Color heatColor);
        HeatMap(swt::HeatMap::HeatMapType hmType, swt::SwarmConfig &preset, swt::ThemeConfig &theme);
        void AddHeat(sf::Vector2f point, short value);
        short GetHeat(sf::Vector2f point);
        void TickDown(float strength, float dt);
        void UpdateVisualMap();
    };

}
