#pragma once
#include "Creature.h"
#include "Environment.h"

class Carnivore : public Creature
{
public:
    Carnivore(Environment& environment, float startX, float startY);

    void update(float deltaTime) override;

private:
    void huntPrey();
    void chaseTarget();
};