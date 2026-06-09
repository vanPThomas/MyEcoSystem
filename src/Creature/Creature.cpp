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

    // Decide gender
    brain.dna.setIsMale(MathUtils::randomInt(0, 1) == 1);

}

// ====================== Update Creature ======================
void Creature::update(float deltaTime)
{
    setState();

    // Update brain (hunger, fear, etc.)
    brain.update(deltaTime);

    moveCreature(deltaTime);

    energyDrain(deltaTime);

    clampCreature();
}

// ====================== Set state ======================
void Creature::setState()
{
    // Dead check
    if (energy <= 0 || health <= 0)
    {
        isAlive = false;
        return;
    }
    else if(energy <= 50)
    {
        brain.setCurrentState(Brain::State::SeekingFood);
    }
}

// ====================== Random Movement ======================
void Creature::moveCreature(float deltaTime)
{
    float dx = tx - x;
    float dy = ty - y;
    float distance = std::sqrt(dx*dx + dy*dy);

    // only move if not already very close
    if (distance > 5.0f)
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

// ====================== Draining Energy ======================
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

// ====================== Clamping ======================
// Clamp position and reset target if outside bounds
void Creature::clampCreature()
{
    float size = brain.dna.getSize();
    float maxX = environment.getSimulationSpaceWidth();
    float maxY = environment.getSimulationSpaceHeight();

    // Clamp X
    if (x < size)
    {
        x = size;
        tx = size;
    }
    else if (x > maxX - size)
    {
        x = maxX - size;
        tx = maxX - size;
    }

    // Clamp Y
    if (y < size)
    {
        y = size;
        ty = size;
    }
    else if (y > maxY - size)
    {
        y = maxY - size;
        ty = maxY - size;
    }
}