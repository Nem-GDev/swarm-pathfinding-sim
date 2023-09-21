#include "Colony.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <sstream>
#include <time.h>
#include "HeatMap.hpp"
#include "SwarmPreset.hpp"
#include "ThemePreset.hpp"

using namespace swt;

Colony::Colony(swt::SwarmPreset preset, swt::SwarmAgent agentTemplate)
{
    colonySize = preset.COLONY_SIZE;
    float angleIncrement = 360.0f / colonySize;
    for (int i = 0; i < colonySize; i++)
    {
        SwarmAgent tempAgent(agentTemplate);
        tempAgent.setRotation(i * angleIncrement);
        tempAgent.seed = i * angleIncrement * 643;
        colonyAgents.push_back(tempAgent);
    }
}

void Colony::TickMove(float steps, float dt)
{
    for (unsigned int i = 0; i < colonySize; i++)
    {
        colonyAgents[i].MoveForward(steps, dt);
    }
}

void Colony::TickMoveThreaded(float steps, unsigned short threads, float dt)
{
    usableThreads = threads;
    if (!threadsLive)
    {
        // create threads
        int perThread = colonySize / usableThreads;
        for (int i = 0; i < usableThreads; i++)
        {
            std::thread thread(&swt::Colony::ThreadMoveJob, this, perThread, (i + 1), steps, dt);
            thread.detach();
        }
        threadsLive = true;
    }
    updateThreads = true;
}

void Colony::ThreadMoveJob(int agentsNo, int threadNum, float steps, float dt)
{
    // NOTE: ThreadMoveJob is deprecated -
    bool finalThread = false;
    if (threadNum == usableThreads)
        finalThread = true;

    int startOffset = agentsNo * (threadNum - 1);
    int endOffset = agentsNo * threadNum;
    std::stringstream ss;
    ss << "\nThread Created | Start:  " << startOffset << "| End: " << endOffset;
    std::cout << ss.str();

    while (true)
    {
        if (updateThreads)
        {
            updateThreads = false;
            for (int i = startOffset; i < endOffset; i++)
            {
                colonyAgents[i].MoveForward(steps, dt);
            }
            // DrawColonyThreaded(startOffset, endOffset);
        }
    }
}

void Colony::DrawColonyThreaded(int s, int e)
{
    return;
    //! Currently not working - Window.draw seems incompatible with multi-threading
    for (int i = s; i < e; i++)
    {
        std::cout << "called" << std::endl;
        currentWindow->draw(colonyAgents[i]);
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
