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

    // give creature random health
    float extremeWeirdIndex = MathUtils::randomFloat(-100.0f, 100.0f);
    if (extremeWeirdIndex < -99.0f)
        health = MathUtils::randomFloat(0.0f, 40.0f); //Extremely weak
    else if (extremeWeirdIndex < -90.0f)
        health = MathUtils::randomFloat(40.0f, 70.0f);
    else if (extremeWeirdIndex < -60.0f)
        health = MathUtils::randomFloat(70.0f, 90.0f);
    else if (extremeWeirdIndex < 60.0f)
        health = MathUtils::randomFloat(90.0f, 110.0f); // Normal and common creature health
    else if (extremeWeirdIndex < 90.0f)
        health = MathUtils::randomFloat(110.0f, 130.0f);
    else if (extremeWeirdIndex < 99.0f)
        health = MathUtils::randomFloat(130.0f, 160.0f);
    else
        health = MathUtils::randomFloat(160.0f, 250.0f); //Extremely healthy

    maxHealth = health;
    std::cout << health << "\n";
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