#ifndef STRING_SORT_TESTER_H
#define STRING_SORT_TESTER_H

#include <string>
#include <vector>
#include <functional>
#include <chrono>

class StringSortTester {
public:
    using StringArray = std::vector<std::string>;
    using SortFunction = std::function<void(StringArray&, size_t&)>;

    struct SortResult {
        double timeMillis;
        size_t charComparisons;
    };

    static SortResult testSort(StringArray data, SortFunction sorter);
};

#endif
