#ifndef STRINGMERGESORT_H
#define STRINGMERGESORT_H

#include <vector>
#include <string>
#include <compare>

class StringMergeSort {
public:
    static void sort(std::vector<std::string>& data, size_t& charComparisons);

private:
    static std::pair<std::strong_ordering, int> lcpCompare(const std::string& a, const std::string& b, int k, size_t& cmp);
    static std::vector<std::pair<std::string, int>> merge(
        std::vector<std::pair<std::string, int>>& left,
        std::vector<std::pair<std::string, int>>& right,
        size_t& cmp);
    static std::vector<std::pair<std::string, int>> mergeSortHelper(
        std::vector<std::string>::iterator begin,
        std::vector<std::string>::iterator end,
        size_t& cmp);
};

#endif // STRINGMERGESORT_H
