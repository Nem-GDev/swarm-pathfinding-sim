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
        double alphaConversion;

        std::vector<std::vector<short>> map;
        sf::VertexArray visualMap;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void InitVisualMap();

    public:
        sf::Color baseHeatColor;
        HeatMap(int resolution, sf::Vector2f screen, sf::Color heatColor);
        void AddHeat(sf::Vector2f point, short value);
        void SubtractHeat(short screenXPos, short screenYPos, short value);
        short GetHeat(sf::Vector2f point);
        void TickDown(float strength, float dt);
        void UpdateVisualMap();
    };

}
