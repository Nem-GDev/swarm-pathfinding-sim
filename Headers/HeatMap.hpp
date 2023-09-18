#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

namespace swt
{
    class HeatMap : public sf::Drawable
    {
    private:
        short mapPrecision, screenWidth, screenHeight;
        short mapWidth, mapHeight, visualMapWidth, visualMapHeight;
        int mapSize, visualMapSize;
        std::vector<std::vector<short>> map;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        sf::VertexArray visualMap;
        void InitVisualMap();

    public:
        HeatMap(int resolution, int screenWidth, int screenHeight, sf::Color heatColor);
        void AddHeat(short screenXPos, short screenYPos, short value);
        void SubtractHeat(short screenXPos, short screenYPos, short value);
        short GetHeat(short screenXPos, short screenYPos);
        void TickDown();
        void UpdateVisualMap();
        sf::Color baseHeatColor;
    };

}
