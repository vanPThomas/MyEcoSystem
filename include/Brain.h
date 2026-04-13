#pragma once
#include "DNA.h"

class Brain
{
public:
    // State machine
    enum class State {
        Wandering,
        SeekingFood,
        Fleeing,
        Hunting,
        Mating,
        Resting
    };

    explicit Brain(const DNA& ownerDNA);
    void update(float deltaTime);

    float getFear() const {return fear;}
    float getHunger() const {return hunger;}
    float getTiredness() const {return tiredness;}
    float getAnger() const {return anger;}
    float getCuriosity() const {return curiosity;}
    float getMatingDrive() const {return matingDrive;}
    float getLastSeenFoodTime() const {return lastSeenFoodTime;}
    float getLastSeenPredatorTime() const {return lastSeenPredatorTime;}
    State getCurrentState() const { return currentState; }
    
private:
    // ==================== Current Emotional / Mental State ====================
    float fear          = 0.0f;     // 0.0 calm → 1.0 terrified
    float hunger        = 0.0f;     // 0.0 full → 1.0 starving
    float tiredness     = 0.0f;
    float anger         = 0.0f;
    float curiosity     = 0.0f;     // current level, not the personality trait
    float matingDrive   = 0.0f;     // How "horny" the creature is at this moment. The want to go mating.

    // ==================== Memory / Short-term State ====================
    float lastSeenFoodTime   = 0.0f;
    float lastSeenPredatorTime = 0.0f;

    State currentState = State::Wandering;

    const DNA& dna;     // the DNA belonging to this brain in question.
};