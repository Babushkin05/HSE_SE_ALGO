#ifndef TERNARY_STRING_QUICKSORT_H
#define TERNARY_STRING_QUICKSORT_H

#include <vector>
#include <string>

class TernaryStringQuickSort {
public:
    static void sort(std::vector<std::string>& data, size_t& charComparisons);

private:
    static void sortRecursive(std::vector<std::string>& a, int low, int high, int d, size_t& cmp);
    static char charAt(const std::string& s, int d, size_t& cmp);
};

#endif
