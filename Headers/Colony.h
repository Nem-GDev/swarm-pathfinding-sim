#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "SwarmAgent.h"

namespace swt
{
    class Colony : public sf::Drawable
    {
    private:
        std::vector<SwarmAgent> colonyAgents;
        unsigned int colonySize;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    public:
        Colony(int count, swt::SwarmAgent agentTemplate);
        void TickColonyMove(float steps);
        void DrawColony(sf::RenderWindow &window);
    };
}