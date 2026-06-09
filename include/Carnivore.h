#pragma once
#include "Creature.h"
#include "Environment.h"
#include "Herbivore.h"
#include <iostream>

class Carnivore : public Creature
{
public:
    Carnivore(Environment& environment, float startX, float startY);

    void update(float deltaTime) override;

private:
    Herbivore* targetHerbivore = nullptr;

    void findNearestHerbivore();
    void moveTowardsTarget(float deltaTime);
    void eatTarget();

    // ====================== Constructor functions ======================
    void randomStrength();
    void randomSpeed();
    void randomHealth();

};