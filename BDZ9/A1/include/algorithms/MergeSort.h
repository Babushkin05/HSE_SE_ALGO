#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <string>

class MergeSort {
public:
    static void sort(std::vector<std::string>& data, size_t& charComparisons);

private:
    static void mergeSort(std::vector<std::string>& data, std::vector<std::string>& aux, int low, int high, size_t& cmp);
    static void merge(std::vector<std::string>& data, std::vector<std::string>& aux, int low, int mid, int high, size_t& cmp);
    static bool less(const std::string& a, const std::string& b, size_t& cmp);
};

#endif
