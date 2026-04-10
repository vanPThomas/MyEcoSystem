#pragma once

class DNA
{
public:
    DNA();

    float getSpeed(){return speed;}
    float getVisionRage(){return visionRange;}
    float getSize(){return size;}
    float getStrength(){return strength;}
    bool getIsMale(){ return isMale;}
    float getMetabolism(){return metabolism;}
    float getEnergyEfficiency(){return energyEfficiency;}
    float getAggression(){return aggression;}
    float getCourage(){return courage;}
    float getCuriosity(){return curiosity;}
    float getGregariousness(){return gregariousness;}
    float getLeaderCoefficient(){return leaderCoefficient;}
    float getStealth(){return stealth;}
    float getCreativity(){return creativity;}
    float getIntelligence(){return intelligence;}
    float getFertility(){return fertility;}
    float getSexDrive(){return sexdrive;}
    float getMutationRate(){return mutationRate;}
    float getGestationTime(){return gestationTime;}
    
public:

    // ==================== Core Physical Traits ====================
    float speed = 50.0f;            // movement speed
    float visionRange = 10.0f;      // how far the creature can see
    float size = 10.0f;             // affects collision, energy consumption, intimidation
    float strength = 500.0f;        // damage dealt when attacking / winning fights
    bool isMale = true;             // true: male, false: female

    // ==================== Metabolism & Energy ====================
    float metabolism = 50.0f;       // how fast energy is consumed (higher = needs more food)
    float energyEfficiency = 50.0f; // how much energy gained from food, out of 100

    // ==================== Behavior & Personality ====================
    float aggression = 0.5f;        // 0.0 = peaceful, 1.0 = very aggressive
    float courage = 1.0f;           // willingness to fight when threatened
    float curiosity = 0.5f;         // tendency to explore vs stay in safe areas
    float gregariousness = 1.0f;    // 0.0 = lone wolf, 1.0 = likes to stay near others (flocking)
    float leaderCoefficient = 0.5f; // How likely is the creature to lead or to follow. 0.0 = pure follower, 1.0 = pure leader
    float stealth = 0.5f;           // how liklely it is to stay hidden
    float creativity = 0.5f;        // how creative the creature can be when necessary
    float intelligence = 100.0f;    // the likelyhood a good decision is made and succeeds.

    // ==================== Reproduction ====================
    float fertility = 0.8f;         // how succesful reproduction could be
    float sexdrive = 100.0f;        // how willing it is to reproduce
    float mutationRate = 100.0f;    // how likely mutation occurs in offspring, 0 - 100%
    float gestationTime = 10.0f;    // cooldown between births (in seconds)

    void mutate(float rate);
};