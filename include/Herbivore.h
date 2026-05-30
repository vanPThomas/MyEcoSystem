#pragma once
#include "Creature.h"
#include "Environment.h"
#include "Plant.h"

class Herbivore : public Creature
{
public:
    Herbivore(Environment& environment, float startX, float startY);

    void update(float deltaTime) override;

    float getEnergyPerHealthPoint() const {return energyPerHealthPoint;}
    bool getEaten() const {return eaten;}

    void setEaten(bool isEaten) {eaten = isEaten;}

    
private:
    void findNearestPlant();
    void moveTowardsTarget(float deltaTime);
    void eatTarget();
    
    float energyPerHealthPoint = 0.5f;
    bool eaten = false;

    Plant* targetPlant = nullptr;

};