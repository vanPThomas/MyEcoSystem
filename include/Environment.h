#pragma once
#include <vector>
// #include "Creature.h"
// #include "Plant.h"
#include <cstdlib>   // for rand()
#include <ctime>     // for time()

class Creature;
class Plant;

class Environment
{
public:
    Environment(int width, int height);

private:
    int simulationSpaceWidth = 1000;
    int simulationSpaceHeight = 1000;

    std::vector<std::unique_ptr<Creature>> creatures;
    std::vector<std::unique_ptr<Plant>> plants;

}