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

    bool eaten = false;

private:
    void findNearestPlant();
    void moveTowardsTarget(float deltaTime);

    float energyPerHealthPoint = 0.5f;

    Plant* targetPlant = nullptr;

};