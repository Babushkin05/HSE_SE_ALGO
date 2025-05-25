#ifndef STRING_GENERATOR_H
#define STRING_GENERATOR_H

#include <string>
#include <vector>
#include <random>

enum class DatasetType {
    RANDOM,
    REVERSED,
    NEARLY_SORTED
};

class StringGenerator {
public:
    StringGenerator();

    std::vector<std::string> generateBaseDataset(size_t size, int minLen = 10, int maxLen = 200);

    std::vector<std::string> getDatasetSubset(const std::vector<std::string>& baseData, size_t newSize, DatasetType type, double perturbationRate = 0.02);

private:
    std::string generateRandomString(int length);
    void shuffleSlightly(std::vector<std::string>& data, double rate);

    std::mt19937 rng;
    const std::string CHAR_POOL;
};

#endif
