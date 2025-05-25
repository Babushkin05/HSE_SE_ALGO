#include "StringGenerator.h"
#include <algorithm>
#include <chrono>

StringGenerator::StringGenerator()
    : CHAR_POOL("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-.") {
    rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
}

std::string StringGenerator::generateRandomString(int length) {
    std::uniform_int_distribution<> dist(0, CHAR_POOL.size() - 1);
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += CHAR_POOL[dist(rng)];
    }
    return result;
}

std::vector<std::string> StringGenerator::generateBaseDataset(size_t size, int minLen, int maxLen) {
    std::vector<std::string> result;
    std::uniform_int_distribution<> lenDist(minLen, maxLen);
    for (size_t i = 0; i < size; ++i) {
        result.push_back(generateRandomString(lenDist(rng)));
    }
    return result;
}

void StringGenerator::shuffleSlightly(std::vector<std::string>& data, double rate) {
    size_t swaps = static_cast<size_t>(data.size() * rate);
    std::uniform_int_distribution<> dist(0, data.size() - 1);
    for (size_t i = 0; i < swaps; ++i) {
        size_t a = dist(rng), b = dist(rng);
        std::swap(data[a], data[b]);
    }
}

std::vector<std::string> StringGenerator::getDatasetSubset(const std::vector<std::string>& baseData, size_t newSize, DatasetType type, double perturbationRate) {
    std::vector<std::string> subset(baseData.begin(), baseData.begin() + newSize);

    switch (type) {
        case DatasetType::RANDOM:
            return subset;

        case DatasetType::REVERSED:
            std::sort(subset.begin(), subset.end(), std::greater<>());
            return subset;

        case DatasetType::NEARLY_SORTED:
            std::sort(subset.begin(), subset.end());
            shuffleSlightly(subset, perturbationRate);
            return subset;

        default:
            return subset;
    }
}
