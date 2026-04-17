#pragma once
#include "Brain.h"
#include "DNA.h"
#include "MathUtils.h"

class Creature
{
public:
    Creature(float x, float y);
    float x = 100.0f;
    float y = 100.0f;
    
public:

    float vx = 0.0f; // velocity x
    float vy = 0.0f; // velocity y

    float tx = 0.0f; // target y
    float ty = 0.0f; // target y

    float energy, hungry, fear, age;
    DNA dna;
    Brain brain;

}; 