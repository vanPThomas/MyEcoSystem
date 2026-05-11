#include "Herbivore.h"

Herbivore::Herbivore(Environment& environment, float startX, float startY)
    : Creature(environment, startX, startY)
{
    // Herbivore-specific default DNA adjustments
    brain.dna.setSpeed(45.0f);
    brain.dna.setAggression(0.2f);
    brain.dna.setGregariousness(0.8f);  // herbivores like to stay in groups
    brain.dna.setMetabolism(35.0f);     // lower metabolism
}

void Herbivore::update(float deltaTime)
{
    
    //if (brain.getHunger() > 0.4f)
    if (brain.getCurrentState() == Brain::State::SeekingFood)
    {
        if (targetPlant == nullptr || targetPlant->getHealthPoints())
        {
            findNearestPlant();
        }
        
        if (targetPlant)
        {
            moveTowardsTarget(deltaTime);
        }
        return;
    }

    Creature::update(deltaTime);   // Call base movement / energy drain
}

void Herbivore::findNearestPlant()
{
    targetPlant = nullptr;
    float bestDistanceSq = brain.dna.getVisionRange() * brain.dna.getVisionRange();

    for (auto& plantPtr : environment.plants)
    {   
        Plant* plant = plantPtr.get();
        if (plant->getHealthPoints() <=0) continue;

        float dx = plant->getXPos() - x;
        float dy = plant->getYPos() - y;
        float distSq = dx*dx + dy*dy;

        if (distSq < bestDistanceSq)
        {
            bestDistanceSq = distSq;
            targetPlant = plant;
        }
    }
}

void Herbivore::moveTowardsTarget(float deltaTime)
{
    if (!targetPlant) return;

    float dx = targetPlant->getXPos() - x;
    float dy = targetPlant->getYPos() - y;
    float distance = std::sqrt(dx*dx + dy*dy);

    if (distance < 1.0f)
    {
        // Eat the plant!
        // energy += targetPlant->energyValue;
        // targetPlant->eaten = true;
        // targetPlant = nullptr;
        // brain.setState(Brain::State::Wandering);
        return;
    }

    // Move towards it
    float speed = brain.dna.getSpeed() * deltaTime;
    x += (dx / distance) * speed;
    y += (dy / distance) * speed;
}