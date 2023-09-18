#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

namespace swt
{
    class HeatMap
    {
    private:
        int resolution;
        std::vector<std::vector<unsigned short>> map;

    public:
        HeatMap(int resolution, int screenWidth, int screenHeight);
    };

}
