#include "Herbivore.h"
#include <iostream>

Herbivore::Herbivore(Environment& environment, float startX, float startY)
    : Creature(environment, startX, startY)
{
    // Herbivore-specific default DNA adjustments
    brain.dna.setSpeed(45.0f);
    brain.dna.setAggression(0.2f);
    brain.dna.setGregariousness(0.8f);  // herbivores like to stay in groups
    brain.dna.setMetabolism(35.0f);     // lower metabolism

    // give herbivore random strength
    float extremeWeirdIndex = MathUtils::randomFloat(0, 100.0f);
    float herbStrength = 0.0f;
    if (extremeWeirdIndex < 0.5f)
        herbStrength = MathUtils::randomFloat(0.0f, 200.0f); // 0.5% chance for extremely weak strength
    else if (extremeWeirdIndex < 5.0f)
        herbStrength = MathUtils::randomFloat(200.0f, 300.0f); // 4.5% chance for weak strength
    else if (extremeWeirdIndex < 20.0f)
        herbStrength = MathUtils::randomFloat(300.0f, 350.0f); // 15% chance for below average strength
    else if (extremeWeirdIndex < 80.0f)
        herbStrength = MathUtils::randomFloat(350.0f, 450.0f); // 60% chance for Normal and common creature strength
    else if (extremeWeirdIndex < 95.0f)
        herbStrength = MathUtils::randomFloat(450.0f, 500.0f); // 15% chance for above average strength
    else if (extremeWeirdIndex < 99.5f)
        herbStrength = MathUtils::randomFloat(500.0f, 700.0f); // 4.5% chance for high strength
    else
        herbStrength = MathUtils::randomFloat(700.0f, 1500.0f); //0.5% for Extremely high strength

    // Strength debugger
    if (herbStrength > 500.0f)
        std::cout << "Abnormally High Strength (herb): " + std::to_string(herbStrength) << "\n";
    if (herbStrength < 300.0f)
        std::cout << "Abnormally Low Strength (herb): " + std::to_string(herbStrength) << "\n";

    brain.dna.setStrength(herbStrength);
}

// ====================== Update Herbivore ======================
void Herbivore::update(float deltaTime)
{
    age += deltaTime;

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
    }

    if(!targetPlant)
    {
        Creature::update(deltaTime);   // Call base movement / energy drain
    }

}

// ====================== Eat plant ======================
// Find nearest plant
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

// Move to target and eat it
void Herbivore::moveTowardsTarget(float deltaTime)
{
    if (!targetPlant) return;

    float dx = targetPlant->getXPos() - x;
    float dy = targetPlant->getYPos() - y;
    float distance = std::sqrt(dx*dx + dy*dy);

    if (distance < 1.0f)
    {
        eatTarget();
        return;
    }

    // Move towards it
    float speed = brain.dna.getSpeed() * deltaTime;
    x += (dx / distance) * speed;
    y += (dy / distance) * speed;
}

void Herbivore::eatTarget()
{
    // Eat the plant!
    energy += targetPlant->getHealthPoints() * targetPlant->getEnergyPerHealthPoint();
    targetPlant->eaten = true;
    targetPlant = nullptr;
    brain.setCurrentState(Brain::State::Wandering);
}