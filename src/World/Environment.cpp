#include "Environment.h"

Environment::Environment(int width, int height)
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

void UIManager::SpawnRandomCreature()
{
    float randomX = static_cast<float>(rand() % simulationScreenWidth);
    float randomY = static_cast<float>(rand() % simulationScreenHeight);

    Creature newCreature(randomX, randomY, simulationScreenWidth, simulationScreenHeight);
    creatures.push_back(newCreature);
}
void UIManager::SpawnRandomPlant()
{
    float randomX = static_cast<float>(rand() % simulationScreenWidth);
    float randomY = static_cast<float>(rand() % simulationScreenHeight);

    Plant newPlant(randomX, randomY, simulationScreenWidth, simulationScreenHeight);
    plants.push_back(newPlant);
}