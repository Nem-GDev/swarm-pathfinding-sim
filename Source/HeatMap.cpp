#include "HeatMap.hpp"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

using namespace swt;

HeatMap::HeatMap(int resolution, int screenWidth, int screenHeight, sf::Color heatColor)
{
    this->baseHeatColor = heatColor;
    this->mapPrecision = resolution;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->mapWidth = screenWidth / mapPrecision;
    this->mapHeight = screenHeight / mapPrecision;
    this->map.resize(mapHeight, std::vector<short>(mapWidth, 0));
    this->mapSize = mapWidth * mapHeight;

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

void HeatMap::AddHeat(short screenXPos, short screenYPos, short value)
{
    // TODO: refactor validation to new method
    short sY = std::max((short)0, screenXPos);
    sY = std::min(screenWidth, (short)screenXPos);
    short sX = std::max((short)0, screenYPos);
    sX = std::min(screenHeight, (short)screenYPos);

    short y = sY / mapPrecision;
    short x = sX / mapPrecision;

    map[x][y] += value;
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
short HeatMap::GetHeat(short screenXPos, short screenYPos)
{
    // TODO: refactor validation to new method
    short sY = std::max((short)0, screenXPos);
    sY = std::min(screenWidth, (short)screenXPos);
    short sX = std::max((short)0, screenYPos);
    sX = std::min(screenHeight, (short)screenYPos);

    short y = sY / mapPrecision;
    short x = sX / mapPrecision;

    return map[x][y];
}
void HeatMap::TickDown()
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            // will not go lower than 0
            map[i][j] = std::max((short)0, --map[i][j]);
        }
    }
}
void HeatMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(visualMap, states);
}

void HeatMap::InitVisualMap()
{
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
            tempColor.a = std::min(255, (int)map[i][j]);
            visualMap[currentFirst].color = tempColor;
            visualMap[++currentFirst].color = tempColor;
            visualMap[++currentFirst].color = tempColor;
            visualMap[++currentFirst].color = tempColor;
            ++currentFirst;
        }
    }
}