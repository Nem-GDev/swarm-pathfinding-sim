#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include "SwarmAgent.hpp"
#include "HeatMap.hpp"
#include <time.h>

using namespace swt;

SwarmAgent::SwarmAgent(sf::Color color, sf::Vector2f size, sf::Vector2f position, sf::Vector2f screenSize, HeatMap &hm, float obedience)
{
    this->obedience = obedience;
    this->hm1 = &hm;
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

void SwarmAgent::PathfindTick()
{
    this->setRotation(this->getRotation() + 0.5f);
    this->move(sf::Vector2f(0, -0.5f));
}

// This method scope must be optimized
void SwarmAgent::MoveForward(float steps, float dt)
{
    // rotations
    if (hasMovementNoise)
    {
        currentMovementNoisePoll++;
        if (currentMovementNoisePoll >= movementNoisePR)
            AddMovementNoise(dt);
    }
    FollowHeat(obedience, dt);

    // forward calculation and movement
    CalculateForward();
    this->move(nForward * steps * dt);

    lAntenna.setPosition(this->getTransform().transformPoint(this->getPoint(0)));
    rAntenna.setPosition(this->getTransform().transformPoint(this->getPoint(1)));

    // collision / out of bounds detection
    CheckScreenBounds(screenWidth, screenHeight);
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

void SwarmAgent::AddMovementNoise(float dt)
{
    currentMovementNoisePoll = 0;
    srand(unsigned(seed * (int)time(NULL)));
    int x = rand();
    float change = (x % movementNoiseDirections) * movementNoiseStrength;
    change = ((x % 2) == 0) ? change * -1 : change * 1;
    this->rotate(change * dt);
}

void SwarmAgent::FollowHeat(float strength, float dt)
{
    //! Note: For correct behavior resolution of heatmap needs to be smaller than ant width
    sf::Vector2f lPos(lAntenna.getPosition());
    sf::Vector2f rPos(rAntenna.getPosition());

    short lHeat = hm1->GetHeat(lPos);
    short rHeat = hm1->GetHeat(rPos);

    if (lHeat > rHeat)
    {
        this->rotate(-strength * dt);
    }
    else if (rHeat > lHeat)
    {
        this->rotate(strength * dt);
    }
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