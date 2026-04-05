#pragma once
#include "Brain.h"
#include "DNA.h"

class Creature
{
public:
    Creature() : x(0.0f), y(0.0f) {}
    Creature(float x, float y);
    float x = 100.0f;
    float y = 100.0f;


    // virtual void update(float dt) = 0;
    // virtual render() const = 0;
    
protected:

    float vx = 0.0f; // velocity x
    float vy = 0.0f; // velocity y

    float energy, hungry, fear, age;
    // DNA dna;
    // Brain brain;
    
    // void moveForward(Vector2 target);
    // void fleeFrom(Vector2 threat);
    // void reproduce(Creature& partner);
}; 