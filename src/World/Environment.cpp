#include "Environment.h"
#include "Creature.h"
#include "Plant.h"

Environment::Environment(int width, int height)
    : simulationSpaceWidth(width)
    , simulationSpaceHeight(height)
{
    // Seed random number generator once (at startup)
    srand(static_cast<unsigned int>(time(nullptr)));

    // Spawn the creature at a random position inside the simulation area
    for (int i = 0; i < 10; i++)
    {
        SpawnRandomCreature();
    }
    for (int i = 0; i < 20; i++)
    {
        SpawnRandomPlant();
    }
}

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

void Environment::update(float deltaTime)
{
    // Update all creatures with deltaTime
    for (auto& creature : creatures)
    {
        creature->update(deltaTime);
    }
}