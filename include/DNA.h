#pragma once

class DNA
{
public:
    DNA();
private:

    // ==================== Core Physical Traits ====================
    float speed;           // movement speed
    float visionRange;     // how far the creature can see
    float size;            // affects collision, energy consumption, intimidation
    float strength;        // damage dealt when attacking / winning fights
    bool isMale;           // true: male, false: female

    // ==================== Metabolism & Energy ====================
    float metabolism;       // how fast energy is consumed (higher = needs more food)
    float energyEfficiency; // how much energy gained from food

    // ==================== Behavior & Personality ====================
    float aggression;      // 0.0 = peaceful, 1.0 = very aggressive
    float courage;         // willingness to fight when threatened
    float curiosity;       // tendency to explore vs stay in safe areas
    float gregariousness;  // 0.0 = lone wolf, 1.0 = likes to stay near others (flocking)
    float leaderCoefficient; // How likely is the creature to lead or to follow. 0.0 = pure follower, 1.0 = pure leader
    float stealth;          // how liklely it is to stay hidden
    float creativity;       // how creative the creature can be when necessary
    float intelligence;     // the likelyhood a good decision is made and succeeds.

    // ==================== Reproduction ====================
    float fertility;       // how succesful reproduction could be
    float sexdrive         // how willing it is to reproduce
    float mutationRate;    // how much mutation occurs in offspring
    float gestationTime;   // cooldown between births (in seconds)

    void mutate(float rate);
};