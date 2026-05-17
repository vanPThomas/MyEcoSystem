#include "Creature.h"

Creature::Creature(Environment& environment, float startX, float startY)
    : x(startX)
    , y(startY)
    , brain(DNA())
    , environment(environment)
{
    // Give the creature an initial random target near its starting position
    tx = x + MathUtils::randomFloat(-100.0f, 100.0f);
    ty = y + MathUtils::randomFloat(-100.0f, 100.0f);

    // Give it a small random initial velocity
    vx = MathUtils::randomFloat(-20.0f, 20.0f);
    vy = MathUtils::randomFloat(-20.0f, 20.0f);
}

// Update creature information
void Creature::update(float deltaTime)
{
    setState();

    // Age the creature

    // Update brain (hunger, fear, etc.)
    brain.update(deltaTime);

    moveCreature(deltaTime);

    energyDrain(deltaTime);

    clampCreature();
}

// Set state
void Creature::setState()
{
    // Dead check
    if (energy <= 0)
    {
        isAlive = false;
        return;
    }
    else if(energy <= 50)
    {
        brain.setCurrentState(Brain::State::SeekingFood);
    }
}

// Simple movement towards target using DNA speed
void Creature::moveCreature(float deltaTime)
{
    float dx = tx - x;
    float dy = ty - y;
    float distance = std::sqrt(dx*dx + dy*dy);

    if (distance > 5.0f)   // only move if not already very close
    {
        if (energy < 20)
        {
            // slower speed due to hunger
            float speed = brain.dna.getSpeed()/3;
    
            vx = (dx / distance) * speed;
            vy = (dy / distance) * speed;
    
            // Apply velocity
            x += vx * deltaTime;
            y += vy * deltaTime;
        }
        else
        {
            // Normalize direction and multiply by speed from DNA
            float speed = brain.dna.getSpeed();
    
            vx = (dx / distance) * speed;
            vy = (dy / distance) * speed;
    
            // Apply velocity
            x += vx * deltaTime;
            y += vy * deltaTime;
        }
    }
    else
    {
        // Reached target → pick a new random target
        tx = x + MathUtils::randomFloat(-150.0f, 150.0f);
        ty = y + MathUtils::randomFloat(-150.0f, 150.0f);

        // dampen velocity when reaching target
        vx *= 0.5f;
        vy *= 0.5f;
    }
}

// simple energy drain based on metabolism + movement
void Creature::energyDrain(float deltaTime)
{
    float movementCost = (vx*vx + vy*vy) * 0.1f;
    energy -= ((brain.dna.getMetabolism() + movementCost) * deltaTime)/100;

    if (energy < 0)
    {
        energy = 0;
    }
}

// Clamp position and reset target if outside bounds
void Creature::clampCreature()
{
    int creatureSize = brain.dna.getSize();

    if (x < creatureSize)
    {
        x = creatureSize;
        tx = creatureSize;
    }
    else if (x > environment.getSimulationSpaceWidth() - creatureSize)
    {
        x = environment.getSimulationSpaceWidth() - creatureSize;
        tx = environment.getSimulationSpaceWidth() - creatureSize;
    }

    if (y < creatureSize)
    {
        y = creatureSize;
        ty = creatureSize;
    }
    else if (y > environment.getSimulationSpaceHeight() - creatureSize)
    {
        y = environment.getSimulationSpaceHeight() - creatureSize;
        ty = environment.getSimulationSpaceHeight() - creatureSize;
    }
}