#pragma once
#include <vector>
#include <cstdlib>   // for rand()
#include <ctime>     // for time()
#include <memory>   // for unique_ptr
#include "Environment.h"


class Creature;
class Plant;

class Environment
{
public:
    Environment(Environment& environment, int width, int height);

    void update(float deltaTime);
    
    float getSimulationSpaceWidth() const {return simulationSpaceWidth;}
    float getSimulationSpaceHeight() const {return simulationSpaceHeight;}

    void SpawnRandomCreature();
    void SpawnRandomPlant();

    std::vector<std::unique_ptr<Creature>> creatures;
    std::vector<std::unique_ptr<Plant>> plants;

private:
    int simulationSpaceWidth = 1000;
    int simulationSpaceHeight = 1000;
};