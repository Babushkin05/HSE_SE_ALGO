#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>

#include "StringGenerator.h"
#include "StringSortTester.h"

#include "algorithms/QuickSort.h"
#include "algorithms/MergeSort.h"
#include "algorithms/TernaryStringQuickSort.h"
#include "algorithms/StringMergeSort.h"
#include "algorithms/MSDRadixSort.h"
#include "algorithms/MSDRadixSortWithQuick.h"

namespace fs = std::filesystem;

using StringArray = std::vector<std::string>;
using SortFunction = StringSortTester::SortFunction;
using DatasetType = DatasetType;

void saveResultRow(std::ofstream& out, size_t size, const StringSortTester::SortResult& result) {
    out << size << "," << std::fixed << std::setprecision(3)
        << result.timeMillis << "," << result.charComparisons << "\n";
}

SortFunction getQuickSortFunc() {
    return [](StringArray& data, size_t& cmp) {
        QuickSort::sort(data, cmp);
    };
}

SortFunction getMergeSortFunc() {
    return [](StringArray& data, size_t& cmp) {
        MergeSort::sort(data, cmp);
    };
}

SortFunction getTernaryQuickFunc() {
    return [](StringArray& data, size_t& cmp) {
        TernaryStringQuickSort::sort(data, cmp);
    };
}

SortFunction getStringMergeSortFunc() {
    return [](StringArray& data, size_t& cmp) {
        StringMergeSort::sort(data, cmp);
    };
}

SortFunction getMSDRadixFunc() {
    return [](StringArray& data, size_t& cmp) {
        MSDRadixSort::sort(data, cmp);
    };
}

SortFunction getMSDRadixWithQuickFunc() {
    return [](StringArray& data, size_t& cmp) {
        MSDRadixSortWithQuick::sort(data, cmp);
    };
}

int main() {
    const std::vector<DatasetType> types = {
        DatasetType::RANDOM,
        DatasetType::REVERSED,
        DatasetType::NEARLY_SORTED
    };

    const std::vector<std::string> typeNames = {
        "random",
        "reversed",
        "almost_sorted"
    };

    const std::vector<std::pair<std::string, SortFunction>> sorters = {
        {"QuickSort", getQuickSortFunc()},
        {"MergeSort", getMergeSortFunc()},
        {"TernaryStringQuickSort", getTernaryQuickFunc()},
        {"StringMergeSort", getStringMergeSortFunc()},
        {"MSDRadixSort", getMSDRadixFunc()},
        {"MSDRadixSortWithQuick", getMSDRadixWithQuickFunc()}
    };

    const int repeats = 5;
    const std::string resultDir = "results";
    const int maxSize = 3000;
    const int step = 100;

    fs::create_directory(resultDir);

    StringGenerator generator;

    for (size_t typeIndex = 0; typeIndex < types.size(); ++typeIndex) {
        DatasetType dtype = types[typeIndex];
        std::string dtypeStr = typeNames[typeIndex];

        auto base = generator.generateBaseDataset(maxSize);

        // Подготовка файлов
        std::unordered_map<std::string, std::ofstream> files;
        for (const auto& [name, _] : sorters) {
            std::string path = resultDir + "/" + name + "_" + dtypeStr + ".csv";
            files[name].open(path);
            files[name] << "Size,AvgTime(ms),AvgComparisons\n";
        }

        for (int size = step; size <= maxSize; size += step) {
            auto subset = generator.getDatasetSubset(base, size, dtype);

            for (const auto& [name, sorter] : sorters) {
                double totalTime = 0.0;
                size_t totalCmp = 0;

                for (int i = 0; i < repeats; ++i) {
                    auto data = subset;
                    auto result = StringSortTester::testSort(data, sorter);
                    totalTime += result.timeMillis;
                    totalCmp += result.charComparisons;
                }

                StringSortTester::SortResult avgResult {
                    totalTime / repeats,
                    totalCmp / repeats
                };

                saveResultRow(files[name], size, avgResult);
            }

            std::cout << "Done " << dtypeStr << " size " << size << '\n';
        }

        for (auto& [_, f] : files) f.close();
    }

    std::cout << "All tests completed.\n";
    return 0;
}
