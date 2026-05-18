#include "Carnivore.h"

Carnivore::Carnivore(Environment& environment, float startX, float startY)
    : Creature(environment, startX, startY)
{
    // Carnivore-specific DNA defaults
    brain.dna.setSpeed(70.0f);          // faster
    brain.dna.setAggression(0.85f);     // much more aggressive
    brain.dna.setStrength(800.0f);
    brain.dna.setMetabolism(65.0f);     // higher metabolism (needs more food) 
    brain.dna.setVisionRange(220.0f);   // better vision for hunting
}

void Carnivore::update(float deltaTime)
{
    age += deltaTime;

    Creature::update(deltaTime);

}

void Herbivore::findNearestHerbivore()
{
    targetHerbivore = nullptr;
    float bestDistanceSq = brain.dna.getVisionRange() * brain.dna.getVisionRange();

    for (auto& c : environment.creatures)
    {   
        if (Herbivore* herb = dynamic_cast<Herbivore*>(c))
        {
            Herbivore* herb = c.get();
            if (herb->getHealthPoints() <=0) continue;
    
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
}