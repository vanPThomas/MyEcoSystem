#pragma once
#include "Creature.h"
#include "Environment.h"
#include "Plant.h"

class Herbivore : public Creature
{
public:
    Herbivore(Environment& environment, float startX, float startY);

    void update(float deltaTime) override;

    // ====================== GETTERS ======================
    float getEnergyPerHealthPoint() const {return energyPerHealthPoint;}
    float getOriginalHealthPoints() const {return originalHealthPoints;}
    bool getEaten() const {return eaten;}

    // ====================== SETTERS ======================
    void setEaten(bool isEaten) {eaten = isEaten;}

    
private:
    void findNearestPlant();
    void moveTowardsTarget(float deltaTime);
    void eatTarget();

    // ====================== Constructor functions ======================
    void randomStrength();
    void randomSpeed();
    void randomHealth();
    void randomMetabolism();

    
    float energyPerHealthPoint = 0.5f;
    float originalHealthPoints = 100.0f;
    bool eaten = false;

    Plant* targetPlant = nullptr;

};