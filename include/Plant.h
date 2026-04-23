#pragma once

class Plant
{
public:
    Plant(float startX, float startY);

    float getHealthPoints() const {return healthPoints;}
    float getEnergyPerHealthPoint() const {return energyPerHealthPoint;}
    float getPoisonLevel() const {return poisonLevel;}
    float getAge() const {return age;}

    float x = 0.0f;
    float y = 0.0f;
    
private:
    float healthPoints = 100; // how much there is to eat
    float energyPerHealthPoint = 0.5f;   // how much energy is provided to creature per eaten health point
    float poisonLevel = 5.0f;   // how dangerous this plant is to eat, out of 10.
    float age = 0.0f;
}