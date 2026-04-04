#pragma once
struct DNA {
    float speed;
    float vision;
    float aggression;

    static DNA crossover(const DNA& a, const DNA& b);
    static DNA mutate(const DNA& original, float b)
}