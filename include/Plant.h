#pragma once

class Plant
{
public:

private:
    int healthPoints = 100; // how much there is to eat
    float energyPerHealthPoint = 0.5f;   // how much energy is provided to creature per eaten health point
    float poisonLevel = 5.0f;   // how dangerous this plant is to eat, out of 10.
    float age = 0.0f;
}