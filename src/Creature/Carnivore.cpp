#include "Carnivore.h"

Carnivore::Carnivore(Environment& environment, float startX, float startY)
    : Creature(environment, startX, startY)
{
    // Carnivore-specific DNA defaults
    brain.dna.setAggression(0.85f);     // much more aggressive
    brain.dna.setVisionRange(220.0f);   // better vision for hunting
    
    randomStrength();
    randomSpeed();
    randomHealth();
    randomMetabolism();

}

// ====================== Constructor functions ======================
// give Carnivore random strength
void Carnivore::randomStrength()
{
    float extremeWeirdIndex = MathUtils::randomFloat(0, 100.0f);
    float CarnStrength = 0.0f;
    if (extremeWeirdIndex < 0.5f)
        CarnStrength = MathUtils::randomFloat(0.0f, 400.0f); // 0.5% chance for extremely weak strength
    else if (extremeWeirdIndex < 5.0f)
        CarnStrength = MathUtils::randomFloat(400.0f, 600.0f); // 4.5% chance for weak strength
    else if (extremeWeirdIndex < 20.0f)
        CarnStrength = MathUtils::randomFloat(600.0f, 700.0f); // 15% chance for below average strength
    else if (extremeWeirdIndex < 80.0f)
        CarnStrength = MathUtils::randomFloat(700.0f, 900.0f); // 60% chance for Normal and common creature strength
    else if (extremeWeirdIndex < 95.0f)
        CarnStrength = MathUtils::randomFloat(900.0f, 1000.0f); // 15% chance for above average strength
    else if (extremeWeirdIndex < 99.5f)
        CarnStrength = MathUtils::randomFloat(1000.0f, 1200.0f); // 4.5% chance for high strength
    else
        CarnStrength = MathUtils::randomFloat(1200.0f, 2000.0f); //0.5% for Extremely high strength

    // Strength debugger
    if (CarnStrength > 1200.0f)
        std::cout << "Abnormally High Strength (carn): " + std::to_string(CarnStrength) << "\n";
    if (CarnStrength < 600.0f)
        std::cout << "Abnormally Low Strength (carn): " + std::to_string(CarnStrength) << "\n";

    brain.dna.setStrength(CarnStrength);
}

// give Carnivore random speed
void Carnivore::randomSpeed()
{
    float extremeWeirdIndex = MathUtils::randomFloat(0, 100.0f);
    float CarnSpeed = 0.0f;
    if (extremeWeirdIndex < 0.5f)
        CarnSpeed = MathUtils::randomFloat(0.0f, 40.0f); // 0.5% chance for extremely slow speed
    else if (extremeWeirdIndex < 5.0f)
        CarnSpeed = MathUtils::randomFloat(40.0f, 50.0f); // 4.5% chance for slow speed
    else if (extremeWeirdIndex < 20.0f)
        CarnSpeed = MathUtils::randomFloat(50.0f, 60.0f); // 15% chance for below average speed
    else if (extremeWeirdIndex < 80.0f)
        CarnSpeed = MathUtils::randomFloat(60.0f, 80.0f); // 60% chance for Normal and common creature speed
    else if (extremeWeirdIndex < 95.0f)
        CarnSpeed = MathUtils::randomFloat(80.0f, 90.0f); // 15% chance for above average speed
    else if (extremeWeirdIndex < 99.5f)
        CarnSpeed = MathUtils::randomFloat(90.0f, 110.0f); // 4.5% chance for high speed
    else
        CarnSpeed = MathUtils::randomFloat(110.0f, 150.0f); //0.5% for Extremely high speed

    // Speed debugger
    if (CarnSpeed > 90.0f)
        std::cout << "Abnormally High Speed (carn): " + std::to_string(CarnSpeed) << "\n";
    if (CarnSpeed < 50.0f)
        std::cout << "Abnormally Low Speed (carn): " + std::to_string(CarnSpeed) << "\n";

    brain.dna.setSpeed(CarnSpeed);
}

void Carnivore::randomHealth()
{
    // give creature random health
    float extremeWeirdIndex = MathUtils::randomFloat(0, 100.0f);
    if (extremeWeirdIndex < 0.5f)
        health = MathUtils::randomFloat(0.0f, 40.0f); // 0.5% chance for extremely weak health
    else if (extremeWeirdIndex < 5.0f)
        health = MathUtils::randomFloat(40.0f, 70.0f); // 4.5% chance for weak Health
    else if (extremeWeirdIndex < 20.0f)
        health = MathUtils::randomFloat(70.0f, 90.0f); // 15% chance for below average health
    else if (extremeWeirdIndex < 80.0f)
        health = MathUtils::randomFloat(90.0f, 110.0f); // 60% chance for Normal and common creature health
    else if (extremeWeirdIndex < 95.0f)
        health = MathUtils::randomFloat(110.0f, 130.0f); // 15% chance for above average Health
    else if (extremeWeirdIndex < 99.5f)
        health = MathUtils::randomFloat(130.0f, 160.0f); // 4.5% chance for strong Health
    else
        health = MathUtils::randomFloat(160.0f, 250.0f); //0.5% for Extremely strong extremely healthy

    maxHealth = health;

    // Health debugger
    if (health > 130.0f)
        std::cout << "Abnormally High Health (Carn): " + std::to_string(health) << "\n";
    if (health < 70.0f)
        std::cout << "Abnormally Low Health (Carn): " + std::to_string(health) << "\n";
}

void Carnivore::randomMetabolism()
{
    // give creature random health
    float extremeWeirdIndex = MathUtils::randomFloat(0, 100.0f);
    float herbMetabolism = 35.0f;

    if (extremeWeirdIndex < 0.5f)
        herbMetabolism = MathUtils::randomFloat(15.0f, 45.0f); // 0.5% chance for extremely low Metabolism
    else if (extremeWeirdIndex < 5.0f)
        herbMetabolism = MathUtils::randomFloat(45.0f, 55.0f); // 4.5% chance for low Metabolism
    else if (extremeWeirdIndex < 20.0f)
        herbMetabolism = MathUtils::randomFloat(55.0f, 60.0f); // 15% chance for below average Metabolism
    else if (extremeWeirdIndex < 80.0f)
        herbMetabolism = MathUtils::randomFloat(60.0f, 70.0f); // 60% chance for Normal and common Metabolism
    else if (extremeWeirdIndex < 95.0f)
        herbMetabolism = MathUtils::randomFloat(70.0f, 75.0f); // 15% chance for above average metabolism
    else if (extremeWeirdIndex < 99.5f)
        herbMetabolism = MathUtils::randomFloat(75.0f, 85.0f); // 4.5% chance for high Metabolism
    else
        herbMetabolism = MathUtils::randomFloat(85.0f, 120.0f); //0.5% for Extremely high Metabolism

    // Metabolism debugger
    if (herbMetabolism > 75.0f)
        std::cout << "Abnormally High Metabolism (Carn): " + std::to_string(herbMetabolism) << "\n";
    if (herbMetabolism < 55.0f)
        std::cout << "Abnormally Low Metabolism (Carn): " + std::to_string(herbMetabolism) << "\n";

    brain.dna.setMetabolism(herbMetabolism);
}

// ====================== Update Carnivore ======================
void Carnivore::update(float deltaTime)
{
    age += deltaTime;

    if (brain.getCurrentState() == Brain::State::SeekingFood || brain.getCurrentState() == Brain::State::Hunting)
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
    brain.setCurrentState(Brain::State::Hunting);
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
    energy += targetHerbivore->getEdibleHealthPoints() * targetHerbivore->getEnergyPerHealthPoint();
    targetHerbivore->setEaten(true);
    targetHerbivore = nullptr;
    brain.setCurrentState(Brain::State::Wandering);
}