#pragma once

class Plant
{
public:
    Plant(float startX, float startY, int spaceWidth, int spaceHeight);

    float getHealthPoints() const {return healthPoints;}
    float getEnergyPerHealthPoint() const {return energyPerHealthPoint;}
    float getPoisonLevel() const {return poisonLevel;}
    float getAge() const {return age;}
    float getXPos() const {return x;}
    float getYPos() const {return y;}
    
private:
    float x = 0.0f;
    float y = 0.0f;
    float healthPoints = 100; // how much there is to eat
    float energyPerHealthPoint = 0.5f;   // how much energy is provided to creature per eaten health point
    float poisonLevel = 5.0f;   // how dangerous this plant is to eat, out of 10.
    float age = 0.0f;
    int simulationSpaceWidth = 1000;
    int simulationSpaceHeight = 1000;
};