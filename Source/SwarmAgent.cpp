#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include "SwarmAgent.hpp"
#include "HeatMap.hpp"
#include <time.h>

using namespace swt;

SwarmAgent::SwarmAgent(sf::Color color, sf::Vector2f size, sf::Vector2f position, sf::Vector2f screenSize, float obedience)
{
    this->obedience = obedience;
    this->currentPheromoneRange = maxPheromone;
    this->setSize(size);
    this->setPosition(position);
    this->setFillColor(color);
    screenWidth = screenSize.x;
    screenHeight = screenSize.y;
    sf::Vector2f origin((float)size.x / 2, (float)size.y / 2);
    this->setOrigin(origin);
    CalculateForward();
    xOutOfBounds = false;
    yOutOfBounds = false;
}

// This method scope must be optimized
void SwarmAgent::MoveForward(float steps, float dt)
{
    // rotations
    if (hasMovementNoise)
    {
        currentMovementNoisePoll++;
        if (currentMovementNoisePoll >= movementNoisePR)
            AddMovementNoise(steps, dt);
    }
    FollowMap(obedience, dt);

    // forward calculation and movement
    CalculateForward();
    this->move(nForward * steps * dt);
    // antenna position update
    lAntenna.setPosition(this->getTransform().transformPoint(this->getPoint(0)));
    rAntenna.setPosition(this->getTransform().transformPoint(this->getPoint(1)));

    // collision / out of bounds detection
    CheckScreenBounds(screenWidth, screenHeight);

    // Pheromones & pathing
    ScanForSource();
    EmitPheromone(steps, dt);
}

void SwarmAgent::CalculateForward()
{
    float radianAngle = this->getRotation() * (M_PI / 180);
    float x = sin(radianAngle);
    float y = -cos(radianAngle);
    float hypo = sqrt((x * x + y * y));
    nForward = sf::Vector2f((float)(x / hypo), (float)(y / hypo));
}

void SwarmAgent::CheckScreenBounds(float screenX, float screenY)
{
    sf::FloatRect bounds = this->getGlobalBounds();

    if (bounds.left < 0 || bounds.left + bounds.width > screenX)
    {
        // make sure we bounce only once even if after bounce we hit edge again
        if (!xOutOfBounds)
        {
            this->setRotation(-this->getRotation());
            xOutOfBounds = true;
        }
    }
    else
        xOutOfBounds = false;

    if (bounds.top < 0 || bounds.top + bounds.height > screenY)
    {
        // make sure we bounce only once even if after bounce we hit edge again
        if (!yOutOfBounds)
        {
            this->setRotation(180 - this->getRotation());
            yOutOfBounds = true;
        }
    }
    else
        yOutOfBounds = false;
}

void SwarmAgent::SetMovementNoisePR(int pollRate, float strength, int directions)
{
    hasMovementNoise = true;
    movementNoisePR = pollRate;
    movementNoiseStrength = strength;
    movementNoiseDirections = directions;
}

void SwarmAgent::AddMovementNoise(float steps, float dt)
{
    currentMovementNoisePoll = 0;
    srand(unsigned(seed * (int)time(NULL)));
    int x = rand();
    float change = (x % movementNoiseDirections) * movementNoiseStrength;
    change = ((x % 2) == 0) ? change * -1 : change * 1;
    this->rotate(change * dt * steps);
}

void SwarmAgent::FollowMap(float strength, float dt)
{
    //! Note: For correct behavior resolution of heatmap needs to be smaller than ant width
    // sf::Vector2f lPos(lAntenna.getPosition());
    // sf::Vector2f rPos(rAntenna.getPosition());
    // short lPheromones;
    // short rPheromones;
    sf::Vector2f lPos(lAntenna.getPosition());
    sf::Vector2f rPos(rAntenna.getPosition());
    short foodPathFoundL;
    short foodPathFoundR;
    short homePathFoundL;
    short homePathFoundR;

    foodPathFoundL = toFood->GetHeat(lPos);
    foodPathFoundR = toFood->GetHeat(rPos);
    homePathFoundL = toHome->GetHeat(lPos);
    homePathFoundR = toHome->GetHeat(rPos);

    if (currentPheromone == Pheromone::FoundFood)
    {
        if (homePathFoundL > homePathFoundR)
        {
            this->rotate(-strength * dt);
        }
        else if (homePathFoundR > homePathFoundL)
        {
            this->rotate(strength * dt);
        }
    }
    else if (currentPheromone == Pheromone::DepartingHome)
    {
        if (foodPathFoundL > foodPathFoundR)
        {
            this->rotate(-strength * dt);
        }
        else if (foodPathFoundR > foodPathFoundL)
        {
            this->rotate(strength * dt);
        }
    }
    else if (currentPheromone == Pheromone::Lost)
    {
        if (homePathFoundL > homePathFoundR)
        {
            this->rotate(-strength * dt);
        }
        else if (homePathFoundL > homePathFoundR)
        {
            this->rotate(strength * dt);
        }
        else if (foodPathFoundL > foodPathFoundR)
        {
            this->rotate(-strength * dt);
        }
        else if (foodPathFoundR > foodPathFoundL)
        {
            this->rotate(strength * dt);
        }
    }

    // if (lPheromones > rPheromones)
    // {
    //     this->rotate(-strength * dt);
    // }
    // else if (rPheromones > lPheromones)
    // {
    //     this->rotate(strength * dt);
    // }
}

void SwarmAgent::ScanForSource()
{
    sf::Vector2f lPos(lAntenna.getPosition());
    sf::Vector2f rPos(rAntenna.getPosition());
    short foodSourceFoundL;
    short foodSourceFoundR;
    short homeSourceFoundL;
    short homeSourceFoundR;

    foodSourceFoundL = foodSource->GetHeat(lPos);
    foodSourceFoundR = foodSource->GetHeat(rPos);
    homeSourceFoundL = homeSource->GetHeat(lPos);
    homeSourceFoundR = homeSource->GetHeat(rPos);

    if (foodSourceFoundL > 0 || foodSourceFoundR > 0)
    {
        if (currentPheromone != Pheromone::FoundFood)
            this->rotate(180);
        currentPheromone = Pheromone::FoundFood;
        currentPheromoneRange = maxPheromone;
    }
    else if (homeSourceFoundL || 0 && homeSourceFoundR > 0)
    {
        if (currentPheromone != Pheromone::DepartingHome)
            this->rotate(180);
        currentPheromone = Pheromone::DepartingHome;
        currentPheromoneRange = maxPheromone;
    }
}

void SwarmAgent::EmitPheromone(float steps, float dt)
{
    if (currentPheromone == Pheromone::Lost)
        return;
    pherDeduct = currentPheromoneRange - dt * steps * (double)pheromoneDepletion;
    currentPheromoneRange = std::max(0, (int)pherDeduct);
    if (currentPheromoneRange == 0)
        currentPheromone = Pheromone::Lost;
    if (currentPheromone == Pheromone::DepartingHome)
    {
        toHome->AddHeat(this->getPosition(), (short)currentPheromoneRange);
    }
    else if (currentPheromone == Pheromone::FoundFood)
    {
        toFood->AddHeat(this->getPosition(), (short)currentPheromoneRange);
    }
}

void SwarmAgent::SetPheromoneMaps(HeatMap &toHome, HeatMap &toFood)
{
    this->toHome = &toHome;
    this->toFood = &toFood;
}

void SwarmAgent::SetSourceMaps(HeatMap &homeSource, HeatMap &foodSource, float pheromoneDepletion, float maxPheromone)
{
    this->homeSource = &homeSource;
    this->foodSource = &foodSource;
    this->pheromoneDepletion = pheromoneDepletion;
    this->maxPheromone = maxPheromone;
    currentPheromoneRange = maxPheromone;
}

sf::RectangleShape SwarmAgent::DebugRAntenna()
{
    sf::RectangleShape rA(sf::Vector2f(4, 4));
    rA.setFillColor(sf::Color::Red);
    rA.setPosition(rAntenna.getPosition());
    return rA;
}
sf::RectangleShape SwarmAgent::DebugLAntenna()
{
    sf::RectangleShape lA(sf::Vector2f(4, 4));
    lA.setFillColor(sf::Color::Cyan);
    lA.setPosition(lAntenna.getPosition());
    return lA;
}
