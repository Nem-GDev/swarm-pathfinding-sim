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
        bool updateThreads = false;
        bool threadsLive = false;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void ThreadMoveJob(int agentsNo, int threadCount, float steps, float dt);
        void DrawColonyThreaded(int s, int e);

    public:
        Colony(swt::SwarmPreset preset, swt::SwarmAgent agentTemplate);
        void TickMove(float steps, float dt);
        void TickMoveThreaded(float steps, unsigned short threads, float dt);
        void DrawColony(sf::RenderWindow &window);
        sf::RenderWindow *currentWindow;
    };
}