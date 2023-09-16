#include "Colony.h"
#include <SFML/Graphics.hpp>

using namespace swt;

Colony::Colony(int count, swt::SwarmAgent agentTemplate)
{
    colonySize = count;
    float angleIncrement = 360.0f / count;
    for (unsigned int i = 0; i < count; i++)
    {
        SwarmAgent tempAgent(agentTemplate);
        tempAgent.setRotation(i * angleIncrement);
        colonyAgents.push_back(tempAgent);
    }
}

void Colony::TickColonyMove(float steps)
{
    for (unsigned int i = 0; i < colonySize; i++)
    {
        colonyAgents[i].MoveForward(steps);
    }
}

void Colony::DrawColony(sf::RenderWindow &window)
{
    for (unsigned int i = 0; i < colonySize; i++)
    {
        window.draw(colonyAgents[i]);
    }
}

void Colony::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < colonySize; i++)
    {
        target.draw(colonyAgents[i], states);
    }
}
