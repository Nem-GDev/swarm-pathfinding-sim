#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "SwarmAgent.h"
#include <thread>

namespace swt
{
    class Colony : public sf::Drawable
    {
    private:
        std::vector<SwarmAgent> colonyAgents;
        unsigned int colonySize;
        unsigned short usableThreads;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void ThreadMoveJob(int agentsNo, int threadCount, float steps);
        bool threadsLive = false;
        bool updateThreads = false;
        // std::vector<std::thread> threads;
        void DrawColonyThreaded(int s, int e);

    public:
        Colony(int count, swt::SwarmAgent agentTemplate);
        void TickMove(float steps);
        void TickMoveThreaded(float steps, unsigned short threads);
        void DrawColony(sf::RenderWindow &window);
        void SetCurrentWindow(sf::RenderWindow &window);
        sf::RenderWindow *currentWindow;
    };
}