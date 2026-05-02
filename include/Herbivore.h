#pragma once
#include "Creature.h"

class Herbivore : public Creature
{
public:
    Herbivore(Environment& environment, float startX, float startY);

    void update(float deltaTime) override;

private:
    void seekFood();        // logic for finding plants
    void fleeFromPredators();
};