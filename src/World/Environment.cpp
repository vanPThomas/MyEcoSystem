#include "Environment.h"
#include "Creature.h"
#include "Plant.h"
#include "Carnivore.h"
#include "Herbivore.h"

Environment::Environment(int width, int height)
    : simulationSpaceWidth(width)
    , simulationSpaceHeight(height)
{
    // Seed random number generator once (at startup)
    srand(static_cast<unsigned int>(time(nullptr)));

    // Spawn the creature at a random position inside the simulation area
    for (int i = 0; i < 20; i++)
    {
        SpawnRandomPlant();
    }
    for (int i = 0; i < 5; i++)
    {
        SpawnRandomCarnivore();
    }
        for (int i = 0; i < 10; i++)
    {
        SpawnRandomHerbivore();
    }
}

// ====================== Update Environment ======================
void Environment::update(float deltaTime)
{
    std::vector<std::unique_ptr<Creature>> newlyDead;
    
    for (auto& c : creatures)
    {
        // Update all creatures with deltaTime
        c->update(deltaTime);

        if (!c->getIsAlive())
            newlyDead.push_back(std::move(c));
    }

    // Remove all dead creaturs
    creatures.erase(std::remove_if(creatures.begin(), creatures.end(), [](const auto& ptr){ return !ptr || !ptr->getIsAlive(); }), creatures.end());

    // Move them to dead list
    for (auto& d : newlyDead)
        deadCreatures.push_back(std::move(d));


    std::vector<std::unique_ptr<Plant>> newlyDeadPlants;
    
    for (auto& p : plants)
    {
        if (p->eaten)
            newlyDeadPlants.push_back(std::move(p));
    }

    // Remove all dead plants
    plants.erase(std::remove_if(plants.begin(), plants.end(), [](const auto& ptr){ return !ptr || ptr->eaten; }), plants.end());

    // Move them to dead list
    for (auto& dp : newlyDeadPlants)
        deadPlants.push_back(std::move(dp));

    const float plantSpawnChancePerFrame = 0.003f;     // ~3% chance per frame → roughly 2 plants per second at 60 FPS

    if (MathUtils::randomFloat(0.0f, 1.0f) < plantSpawnChancePerFrame)   // using your random helper
    {
        SpawnRandomPlant();
    }
}

// ====================== Spawn wildlife ======================
void Environment::SpawnRandomCreature()
{
    float randomX = static_cast<float>(rand() % simulationSpaceWidth);
    float randomY = static_cast<float>(rand() % simulationSpaceHeight);

    // Create unique_ptr and pass Environment reference
    auto newCreature = std::make_unique<Creature>(*this, randomX, randomY);
    creatures.push_back(std::move(newCreature));
}

void Environment::SpawnRandomPlant()
{
    float randomX = static_cast<float>(rand() % simulationSpaceWidth);
    float randomY = static_cast<float>(rand() % simulationSpaceHeight);

    auto newPlant = std::make_unique<Plant>(*this, randomX, randomY);
    plants.push_back(std::move(newPlant));
}

void Environment::SpawnRandomHerbivore()
{
    float randomX = static_cast<float>(rand() % simulationSpaceWidth);
    float randomY = static_cast<float>(rand() % simulationSpaceHeight);

    // Create unique_ptr and pass Environment reference
    auto newHerbivore = std::make_unique<Herbivore>(*this, randomX, randomY);
    creatures.push_back(std::move(newHerbivore));
}

void Environment::SpawnRandomCarnivore()
{
    float randomX = static_cast<float>(rand() % simulationSpaceWidth);
    float randomY = static_cast<float>(rand() % simulationSpaceHeight);

    // Create unique_ptr and pass Environment reference
    auto newHerbivore = std::make_unique<Carnivore>(*this, randomX, randomY);
    creatures.push_back(std::move(newHerbivore));
}