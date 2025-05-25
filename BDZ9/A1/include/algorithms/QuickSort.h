#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <string>

class QuickSort {
public:
    static void sort(std::vector<std::string>& data, size_t& charComparisons);

private:
    static void quickSort(std::vector<std::string>& data, int low, int high, size_t& cmp);
    static int partition(std::vector<std::string>& data, int low, int high, size_t& cmp);
    static bool less(const std::string& a, const std::string& b, size_t& cmp);
};

#endif
