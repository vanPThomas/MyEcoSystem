#pragma once
#include <vector>
#include <cstdlib>   // for rand()
#include <ctime>     // for time()
#include <memory>   // for unique_ptr
#include <algorithm>
#include "Environment.h"


class Creature;
class Plant;

class Environment
{
public:
    Environment(int width, int height);

    void update(float deltaTime);
    
    // ====================== GETTERS ======================
    float getSimulationSpaceWidth() const {return simulationSpaceWidth;}
    float getSimulationSpaceHeight() const {return simulationSpaceHeight;}

    // Spawners
    void SpawnRandomCreature();
    void SpawnRandomPlant();
    void SpawnRandomCarnivore();
    void SpawnRandomHerbivore();

    // Wildlife lists
    std::vector<std::unique_ptr<Creature>> creatures;
    std::vector<std::unique_ptr<Plant>> plants;

    std::vector<std::unique_ptr<Creature>> deadCreatures;
    std::vector<std::unique_ptr<Plant>> deadPlants;

private:
    int simulationSpaceWidth = 1000;
    int simulationSpaceHeight = 1000;
};