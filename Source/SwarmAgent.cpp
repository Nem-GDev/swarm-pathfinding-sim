#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include "SwarmAgent.h"
#include <time.h>

using namespace swt;

SwarmAgent::SwarmAgent(sf::Color color, sf::Vector2f size, sf::Vector2f position, float screenX, float screenY)
{
    this->setSize(size);
    this->setPosition(position);
    this->setFillColor(color);
    screenWidth = screenX;
    screenHeight = screenY;
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
void SwarmAgent::MoveForward(float steps)
{
    if (hasMovementNoise)
    {
        currentMovementNoisePoll++;
        if (currentMovementNoisePoll >= movementNoisePR)
            AddMovementNoise();
    }

    CalculateForward();
    this->move(nForward * steps);
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

void SwarmAgent::AddMovementNoise()
{
    currentMovementNoisePoll = 0;
    srand(unsigned(seed * (int)time(NULL)));
    int x = rand();
    float change = (x % movementNoiseDirections) * movementNoiseStrength;
    change = ((x % 2) == 0) ? change * -1 : change * 1;
    this->rotate(change);
}