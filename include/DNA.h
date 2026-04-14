#pragma once

class DNA
{
public:
    DNA();
    // ====================== GETTERS ======================
    float getSpeed() const {return speed;}
    float getVisionRange() const {return visionRange;}
    float getSize() const {return size;}
    float getStrength() const {return strength;}
    bool getIsMale() const { return isMale;}

    float getMetabolism() const {return metabolism;}
    float getEnergyEfficiency() const {return energyEfficiency;}

    float getAggression() const {return aggression;}
    float getCourage() const {return courage;}
    float getCuriosity() const {return curiosity;}
    float getGregariousness() const {return gregariousness;}
    float getLeaderCoefficient() const {return leaderCoefficient;}
    float getStealth() const {return stealth;}
    float getCreativity() const {return creativity;}
    float getIntelligence() const {return intelligence;}
    
    float getFertility() const {return fertility;}
    float getSexDrive() const {return sexdrive;}
    float getMutationRate() const {return mutationRate;}
    float getGestationTime() const {return gestationTime;}
    
private:

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