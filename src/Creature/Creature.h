class Creature {
public:
    vector2 position;
    float energy, hungry, fear, age;
    DNA dna;
    Brain brain;

    virtual void update(float dt) = 0;
    virtual render() const = 0;
    
protected:
    void moveForward(Vector2 target);
    void fleeFrom(Vector2 threat);
    void reproduce(Creature& partner);
};