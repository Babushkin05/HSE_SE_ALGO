#include "algorithms/QuickSort.h"
#include <algorithm>

void QuickSort::sort(std::vector<std::string>& data, size_t& charComparisons) {
    quickSort(data, 0, static_cast<int>(data.size()) - 1, charComparisons);
}

void QuickSort::quickSort(std::vector<std::string>& data, int low, int high, size_t& cmp) {
    if (low >= high) return;
    int pivotIndex = partition(data, low, high, cmp);
    quickSort(data, low, pivotIndex - 1, cmp);
    quickSort(data, pivotIndex + 1, high, cmp);
}

int QuickSort::partition(std::vector<std::string>& data, int low, int high, size_t& cmp) {
    std::string pivot = data[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (less(data[j], pivot, cmp)) {
            std::swap(data[++i], data[j]);
        }
    }
    std::swap(data[i + 1], data[high]);
    return i + 1;
}

bool QuickSort::less(const std::string& a, const std::string& b, size_t& cmp) {
    size_t i = 0;
    while (i < a.size() && i < b.size()) {
        ++cmp;
        if (a[i] != b[i]) return a[i] < b[i];
        ++i;
    }
    ++cmp;
    return a.size() < b.size();
}
