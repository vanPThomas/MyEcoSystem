class Brain {
public:
    struct ActionScore {
        std::string action;
        float score;
    };

    ActionScore evaluate(const PerceptionData& input, const DAN& dna, float hunger, float fear);
}