#include "StringSortTester.h"
#include <algorithm>
#include <iostream>

namespace {
    size_t g_charComparisons = 0;

    struct LexicalComparator {
        bool operator()(const std::string& a, const std::string& b) const {
            size_t i = 0;
            while (i < a.size() && i < b.size()) {
                ++g_charComparisons;
                if (a[i] != b[i]) return a[i] < b[i];
                ++i;
            }
            ++g_charComparisons; 
            return a.size() < b.size();
        }
    };
}

StringSortTester::SortResult StringSortTester::testSort(StringArray data, SortFunction sorter) {
    g_charComparisons = 0;

    auto start = std::chrono::high_resolution_clock::now();
    sorter(data, g_charComparisons);
    auto end = std::chrono::high_resolution_clock::now();

    double duration = std::chrono::duration<double, std::milli>(end - start).count();

    return {duration, g_charComparisons};
}
