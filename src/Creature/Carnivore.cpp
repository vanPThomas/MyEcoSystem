#include "Carnivore.h"

Carnivore::Carnivore(Environment& environment, float startX, float startY)
    : Creature(environment, startX, startY)
{
    // Carnivore-specific DNA defaults
    brain.dna.setSpeed(70.0f);          // faster
    brain.dna.setAggression(0.85f);     // much more aggressive
    brain.dna.setStrength(800.0f);
    brain.dna.setMetabolism(65.0f);     // higher metabolism (needs more food) 
    brain.dna.setVisionRange(220.0f);   // better vision for hunting
}

// ====================== Update Carnivore ======================
void Carnivore::update(float deltaTime)
{
    age += deltaTime;

    if (brain.getCurrentState() == Brain::State::SeekingFood)
    {
        if (targetHerbivore == nullptr)
        {
            findNearestHerbivore();
        }
        
        if (targetHerbivore)
        {
            moveTowardsTarget(deltaTime);
        }
    }

    if(!targetHerbivore)
    {
        Creature::update(deltaTime);
    }
}

// ====================== Hunt Herbivore ======================
// Find closest target, either dead or alive
void Carnivore::findNearestHerbivore()
{
    targetHerbivore = nullptr;
    float bestDistanceSq = brain.dna.getVisionRange() * brain.dna.getVisionRange();

    // First try find a dead creature to eat
    for (auto& c : environment.deadCreatures)   // c is std::unique_ptr<Creature>
    {   
        Herbivore* herb = dynamic_cast<Herbivore*>(c.get());

        if (herb == nullptr) 
            continue;                               // Not a herbivore

        if (herb->getHealth() <= 0) 
            continue;                               // Skip dead ones

        float dx = herb->getXPos() - x;
        float dy = herb->getYPos() - y;
        float distSq = dx*dx + dy*dy;

        if (distSq < bestDistanceSq)
        {
            bestDistanceSq = distSq;
            targetHerbivore = herb;
        }
    }
    // Check if a herbivore corpse was found to eat.
    if ( targetHerbivore != nullptr)
    {
        return;
    }
    // Find a living herbivore to hunt
    for (auto& c : environment.creatures)   // c is std::unique_ptr<Creature>
    {   
        Herbivore* herb = dynamic_cast<Herbivore*>(c.get());

        if (herb == nullptr) 
            continue;                               // Not a herbivore

        if (herb->getHealth() <= 0) 
            continue;                               // Skip dead ones

        float dx = herb->getXPos() - x;
        float dy = herb->getYPos() - y;
        float distSq = dx*dx + dy*dy;

        if (distSq < bestDistanceSq)
        {
            bestDistanceSq = distSq;
            targetHerbivore = herb;
        }
    }
}

// Move to to target and eat it
void Carnivore::moveTowardsTarget(float deltaTime)
{
    if (!targetHerbivore) return;

    float dx = targetHerbivore->getXPos() - x;
    float dy = targetHerbivore->getYPos() - y;
    float distance = std::sqrt(dx*dx + dy*dy);

    if (distance < 1.0f)
    {
        if (targetHerbivore->getHealth()<= 0)
        {
            eatTarget();
            return;
        }
        else
        {
            float targethealth = targetHerbivore->getHealth();
            targethealth -= brain.dna.getStrength() * deltaTime;
            targetHerbivore->setHealth(targethealth);
            return;
        }
    }

    // Move towards it
    float speed = brain.dna.getSpeed() * deltaTime;
    x += (dx / distance) * speed;
    y += (dy / distance) * speed;
}

// Eat the target herbivore
void Carnivore::eatTarget()
{
    // Eat the herbivore!
    energy += targetHerbivore->getOriginalHealthPoints() * targetHerbivore->getEnergyPerHealthPoint();
    targetHerbivore->setEaten(true);
    targetHerbivore = nullptr;
    brain.setCurrentState(Brain::State::Wandering);
}