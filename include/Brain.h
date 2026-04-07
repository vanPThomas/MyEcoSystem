#pragma once

class Brain
{
public:
    Brain();

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

    // State machine
    enum class State {
        Wandering,
        SeekingFood,
        Fleeing,
        Hunting,
        Mating,
        Resting
    };
};