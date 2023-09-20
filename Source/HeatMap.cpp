#include "HeatMap.hpp"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

using namespace swt;

HeatMap::HeatMap(int resolution, sf::Vector2f screen, sf::Color heatColor)
{
    this->alphaConversion = 255.00 / 32700.00;
    this->baseHeatColor = heatColor;
    this->mapPrecision = resolution;
    this->screenWidth = screen.x;
    this->screenHeight = screen.y;
    this->mapWidth = screenWidth / mapPrecision;
    this->mapHeight = screenHeight / mapPrecision;
    this->map.resize(mapHeight, std::vector<short>(mapWidth, 0));
    this->mapSize = mapWidth * mapHeight;
    this->mapWRange = mapWidth - 1;
    this->mapHRange = mapHeight - 1;

    this->visualMapWidth = mapWidth * 4;
    this->visualMapSize = mapSize * 4;
    this->visualMap.setPrimitiveType(sf::Quads);
    this->visualMap.resize(visualMapSize);

    std::cout << "\nHeatmap: " << mapWidth << "x" << mapHeight << std::endl;
    std::cout << "Map size: " << mapSize << std::endl;
    std::cout << "Visual map size: " << visualMapSize << std::endl;
    std::cout << "Visual Map Width: " << visualMapWidth << std::endl;

    int b = 0;
    for (int i = 0; i < mapHeight; i++)
    {
        // i = which row we are on
        for (int j = 0; j < mapWidth; j++)
        {
            // j which column to edit
            for (int k = 0; k < 4; k++)
            {
                // 4 grouped vertices corresponding to each Quad
                b++;
            }
        }
    }
    std::cout << "Iterated times: " << b << std::endl;

    InitVisualMap();
}

void HeatMap::AddHeat(sf::Vector2f point, short value)
{
    // TODO: refactor validation to new method
    short y = point.y / mapPrecision;
    short x = point.x / mapPrecision;
    int newVal;

    y = std::max((short)0, y);
    x = std::max((short)0, x);

    y = std::min(mapHRange, y);
    x = std::min(mapWRange, x);

    newVal = map[x][y] + value;
    newVal = std::max(0, newVal);
    newVal = std::min(32700, newVal);
    map[x][y] = newVal;
}
void HeatMap::SubtractHeat(short screenXPos, short screenYPos, short value)
{
    //! Currently deprecated
    // // only use this function for ocasional subtraction
    // int x = screenXPos / resolution;
    // int y = screenYPos / resolution;
    // if(map[x][y] >0)
    // map[x][y] -=
}
short HeatMap::GetHeat(sf::Vector2f point)
{
    // TODO: refactor validation to new method
    short y = point.y / mapPrecision;
    short x = point.x / mapPrecision;

    y = std::max((short)0, y);
    x = std::max((short)0, x);

    y = std::min(mapHRange, y);
    x = std::min(mapWRange, x);

    // iob ??
    return map[x][y];
}
void HeatMap::TickDown(float strength, float dt)
{
    for (int i = 0; i < mapHeight; i++)
    {
        short temp;
        for (int j = 0; j < mapWidth; j++)
        {
            // will not go lower than 0
            temp = map[i][j] - (dt * strength);
            map[i][j] = std::max((short)0, temp);
        }
    }
}
void HeatMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(visualMap, states);
}

void HeatMap::InitVisualMap()
{
    std::cout << "Initing" << std::endl;
    sf::Vector2f v0(0, 0);
    sf::Vector2f v1(0, 0);
    sf::Vector2f v2(0, 0);
    sf::Vector2f v3(0, 0);
    int currentFirst = 0;

    // i = which row we are on
    for (int i = 0; i < mapHeight; i++)
    {
        // resolution of 768 and precision of 4 (192x192)map
        // for i=0 (192times | mapHeight) y has to be 0 4 4 0 , 0 4 4 0...
        v0.y = i * mapPrecision;       // 0
        v1.y = (i + 1) * mapPrecision; // 4
        v2.y = (i + 1) * mapPrecision; // 4
        v3.y = i * mapPrecision;       // 0

        // j which column to edit
        for (int j = 0; j < mapWidth; j++)
        {
            // resolution of 768 and precision of 4 (192x192)map
            // for j=0 (192times | mapwidth) x has to be 0 0 4 4, 4 4 8 8...
            v0.x = j * mapPrecision;       // 0
            v1.x = j * mapPrecision;       // 0
            v2.x = (j + 1) * mapPrecision; // 4
            v3.x = (j + 1) * mapPrecision; // 4

            // elements of visual map we are changing
            // from
            // 0 1 2 3, 4 5 6 7...
            visualMap[currentFirst].position = v0;
            visualMap[currentFirst].color = baseHeatColor;

            visualMap[++currentFirst].position = v1;
            visualMap[currentFirst].color = baseHeatColor;

            visualMap[++currentFirst].position = v2;
            visualMap[currentFirst].color = baseHeatColor;

            visualMap[++currentFirst].position = v3;
            visualMap[currentFirst].color = baseHeatColor;
            ++currentFirst;
        }
    }
}

void HeatMap::UpdateVisualMap()
{
    sf::Vector2f v0(0, 0);
    sf::Vector2f v1(0, 0);
    sf::Vector2f v2(0, 0);
    sf::Vector2f v3(0, 0);
    sf::Color tempColor;
    int currentFirst = 0;
    // i = which row we are on
    for (int i = 0; i < mapHeight; i++)
    {
        // resolution of 768 and precision of 4 (192x192)map
        // for i=0 (192times | mapHeight) y has to be 0 4 4 0 , 0 4 4 0...
        v0.y = i * mapPrecision;       // 0
        v1.y = (i + 1) * mapPrecision; // 4
        v2.y = (i + 1) * mapPrecision; // 4
        v3.y = i * mapPrecision;       // 0

        // j which column to edit
        for (int j = 0; j < mapWidth; j++)
        {
            // resolution of 768 and precision of 4 (192x192)map
            // for j=0 (192times | mapwidth) x has to be 0 0 4 4, 4 4 8 8...
            v0.x = j * mapPrecision;       // 0
            v1.x = j * mapPrecision;       // 0
            v2.x = (j + 1) * mapPrecision; // 4
            v3.x = (j + 1) * mapPrecision; // 4

            // elements of visual map we are changing
            // from
            // 0 1 2 3, 4 5 6 7...
            tempColor = visualMap[currentFirst].color;
            int convertedAlpha = map[j][i] * alphaConversion;

            tempColor.a = std::min(255, convertedAlpha);
            visualMap[currentFirst].color = tempColor;
            visualMap[++currentFirst].color = tempColor;
            visualMap[++currentFirst].color = tempColor;
            visualMap[++currentFirst].color = tempColor;
            ++currentFirst;
        }
    }
}