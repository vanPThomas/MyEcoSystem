#pragma once
#include "DNA.h"

class Brain
{
public:
    explicit Brain(const DNA& ownerDNA);
    void update(float deltaTime);
public:
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

    // State machine
    enum class State {
        Wandering,
        SeekingFood,
        Fleeing,
        Hunting,
        Mating,
        Resting
    };

    State currentState = State::Wandering;

    const DNA& dna;     // the DNA belonging to this brain in question.
};