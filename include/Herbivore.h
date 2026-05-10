#pragma once
#include "Creature.h"
#include "Environment.h"
#include "Plant.h"

class Herbivore : public Creature
{
public:
    Herbivore(Environment& environment, float startX, float startY);

    void update(float deltaTime) override;

private:
    void findNearestPlant();
    void moveTowardsTarget(float deltaTime);

    Plant* targetPlant = nullptr;

};