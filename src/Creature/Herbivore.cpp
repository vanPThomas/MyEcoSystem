#include "Herbivore.h"
#include <iostream>

Herbivore::Herbivore(Environment& environment, float startX, float startY)
    : Creature(environment, startX, startY)
{
    // Herbivore-specific default DNA adjustments
    brain.dna.setAggression(0.2f);
    brain.dna.setGregariousness(0.8f);  // herbivores like to stay in groups
    brain.dna.setMetabolism(35.0f);     // lower metabolism
    
    randomStrength();
    randomSpeed();
    randomHealth();
}

// ====================== Constructor functions ======================
// give herbivore random strength
void Herbivore::randomStrength()
{
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

// give herbivore random speed
void Herbivore::randomSpeed()
{
    float extremeWeirdIndex = MathUtils::randomFloat(0, 100.0f);
    float herbSpeed = 0.0f;
    if (extremeWeirdIndex < 0.5f)
        herbSpeed = MathUtils::randomFloat(0.0f, 30.0f); // 0.5% chance for extremely slow speed
    else if (extremeWeirdIndex < 5.0f)
        herbSpeed = MathUtils::randomFloat(30.0f, 35.0f); // 4.5% chance for slow speed
    else if (extremeWeirdIndex < 20.0f)
        herbSpeed = MathUtils::randomFloat(35.0f, 40.0f); // 15% chance for below average speed
    else if (extremeWeirdIndex < 80.0f)
        herbSpeed = MathUtils::randomFloat(40.0f, 50.0f); // 60% chance for Normal and common creature speed
    else if (extremeWeirdIndex < 95.0f)
        herbSpeed = MathUtils::randomFloat(50.0f, 55.0f); // 15% chance for above average speed
    else if (extremeWeirdIndex < 99.5f)
        herbSpeed = MathUtils::randomFloat(55.0f, 70.0f); // 4.5% chance for high speed
    else
        herbSpeed = MathUtils::randomFloat(70.0f, 100.0f); // 0.5% for Extremely high speed

    // Speed debugger
    if (herbSpeed > 55.0f)
        std::cout << "Abnormally High Speed (herb): " + std::to_string(herbSpeed) << "\n";
    if (herbSpeed < 35.0f)
        std::cout << "Abnormally Low Speed (herb): " + std::to_string(herbSpeed) << "\n";

    brain.dna.setSpeed(herbSpeed);
}

void Herbivore::randomHealth()
{
    // give creature random health
    float extremeWeirdIndex = MathUtils::randomFloat(0, 100.0f);
    if (extremeWeirdIndex < 0.5f)
        health = MathUtils::randomFloat(0.0f, 100.0f); // 0.5% chance for extremely weak health
    else if (extremeWeirdIndex < 5.0f)
        health = MathUtils::randomFloat(100.0f, 120.0f); // 4.5% chance for weak Health
    else if (extremeWeirdIndex < 20.0f)
        health = MathUtils::randomFloat(120.0f, 140.0f); // 15% chance for below average health
    else if (extremeWeirdIndex < 80.0f)
        health = MathUtils::randomFloat(140.0f, 150.0f); // 60% chance for Normal and common creature health
    else if (extremeWeirdIndex < 95.0f)
        health = MathUtils::randomFloat(150.0f, 170.0f); // 15% chance for above average Health
    else if (extremeWeirdIndex < 99.5f)
        health = MathUtils::randomFloat(170.0f, 200.0f); // 4.5% chance for strong Health
    else
        health = MathUtils::randomFloat(200.0f, 300.0f); //0.5% for Extremely strong extremely healthy

    maxHealth = health;

    // Health debugger
    if (health > 150.0f)
        std::cout << "Abnormally High Health (Herb): " + std::to_string(health) << "\n";
    if (health < 120.0f)
        std::cout << "Abnormally Low Health (Herb): " + std::to_string(health) << "\n";
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