#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

namespace swt
{
    class HeatMap : public sf::Drawable
    {
    private:
        short mapPrecision, screenWidth, screenHeight;
        short mapWidth, mapHeight, visualMapWidth, visualMapHeight, mapWRange, mapHRange;
        int mapSize, visualMapSize;
        std::vector<std::vector<short>> map;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        sf::VertexArray visualMap;
        void InitVisualMap();

    public:
        HeatMap(int resolution, int screenWidth, int screenHeight, sf::Color heatColor);
        void AddHeat(sf::Vector2f point, short value);
        void SubtractHeat(short screenXPos, short screenYPos, short value);
        short GetHeat(sf::Vector2f point);
        void TickDown(float dt);
        void UpdateVisualMap();
        sf::Color baseHeatColor;
    };

}
