#pragma once
#include "Creature.h"

class Carnivore : public Creature
{
public:
    Carnivore(float startX, float startY, int spaceWidth, int spaceHeight);

    void update(float deltaTime) override;

private:
    void huntPrey();
    void chaseTarget();
};