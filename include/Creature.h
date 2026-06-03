#pragma once
#include "Brain.h"
#include "MathUtils.h"
#include "Environment.h"
#include <iostream>
#include <algorithm>

class Creature
{
public:
    Creature(Environment& environment, float startX, float startY);

    virtual ~Creature() = default;
    virtual void update(float deltaTime);   // Main update function
    
    // ====================== GETTERS ======================
    float getXPos() const {return x;}
    float getYPos() const {return y;}

    float getAge()  const {return age;}
    float getEnergy() const {return energy;}
    float getHealth() const {return health;}

    bool getIsAlive() const {return isAlive;}

    // ====================== SETTERS ======================
    void setHealth(float newHealth) {health = newHealth;}

    Brain brain;
    
protected:
    void setState();
    void moveCreature(float deltaTime);
    void energyDrain(float deltaTime);
    void clampCreature();

    // Movement and location data
    float x = 0.0f;
    float y = 0.0f;

    float vx = 0.0f;   // velocity x
    float vy = 0.0f;   // velocity y

    float tx = 0.0f;   // current target x
    float ty = 0.0f;   // current target y
    
    // General stats
    float energy = 100.0f;
    float age    = 0.0f;
    float health = 100.0f;

    bool isAlive = true;

    Environment& environment;
};