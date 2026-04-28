#pragma once
#include "Creature.h"

class Herbivore : public Creature
{
public:
    Herbivore(float startX, float startY, int spaceWidth, int spaceHeight);

    void update(float deltaTime) override;

private:
    void seekFood();        // logic for finding plants
    void fleeFromPredators();
};