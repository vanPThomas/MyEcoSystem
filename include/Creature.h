#pragma once
#include "Brain.h"
#include "MathUtils.h"
#include "Environment.h"

class Creature
{
public:
    Creature(Environment& environment, float startX, float startY);

    virtual ~Creature() = default;
    virtual void update(float deltaTime);   // Main update function
    
    float getXPos() const {return x;}
    float getYPos() const {return y;}

    Brain brain;
    
protected:
    
    float x = 0.0f;
    float y = 0.0f;

    float vx = 0.0f;   // velocity x
    float vy = 0.0f;   // velocity y

    float tx = 0.0f;   // current target x
    float ty = 0.0f;   // current target y
    
    float energy = 100.0f;
    float age    = 0.0f;

    Environment& environment;
};