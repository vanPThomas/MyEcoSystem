#pragma once
#include "Brain.h"
#include "MathUtils.h"

class Creature
{
public:
    Creature(float startX, float startY, int spaceWidth, int spaceHeight);

    void update(float deltaTime);   // Main update function

    float x = 0.0f;
    float y = 0.0f;

    
    Brain brain;
    
    
private:

    float vx = 0.0f;   // velocity x
    float vy = 0.0f;   // velocity y

    float tx = 0.0f;   // current target x
    float ty = 0.0f;   // current target y
    
    float energy = 100.0f;
    float age    = 0.0f;

    int simulationSpaceWidth = 1000;
    int simulationSpaceHeight = 1000;
};