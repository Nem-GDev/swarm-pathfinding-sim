#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "SwarmAgent.hpp"
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
        void ThreadMoveJob(int agentsNo, int threadCount, float steps, float dt);
        bool threadsLive = false;
        bool updateThreads = false;
        // std::vector<std::thread> threads;
        void DrawColonyThreaded(int s, int e);

    public:
        Colony(int count, swt::SwarmAgent agentTemplate, HeatMap &hm);
        void TickMove(float steps, float dt);
        void TickMoveThreaded(float steps, unsigned short threads, float dt);
        void DrawColony(sf::RenderWindow &window);
        sf::RenderWindow *currentWindow;
    };
}