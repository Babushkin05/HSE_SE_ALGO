#include "algorithms/MergeSort.h"

void MergeSort::sort(std::vector<std::string>& data, size_t& charComparisons) {
    std::vector<std::string> aux(data.size());
    mergeSort(data, aux, 0, static_cast<int>(data.size()) - 1, charComparisons);
}

void MergeSort::mergeSort(std::vector<std::string>& data, std::vector<std::string>& aux, int low, int high, size_t& cmp) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    mergeSort(data, aux, low, mid, cmp);
    mergeSort(data, aux, mid + 1, high, cmp);
    merge(data, aux, low, mid, high, cmp);
}

void MergeSort::merge(std::vector<std::string>& data, std::vector<std::string>& aux, int low, int mid, int high, size_t& cmp) {
    for (int k = low; k <= high; ++k) {
        aux[k] = data[k];
    }

    int i = low, j = mid + 1;
    for (int k = low; k <= high; ++k) {
        if (i > mid) data[k] = aux[j++];
        else if (j > high) data[k] = aux[i++];
        else if (less(aux[j], aux[i], cmp)) data[k] = aux[j++];
        else data[k] = aux[i++];
    }
}

bool MergeSort::less(const std::string& a, const std::string& b, size_t& cmp) {
    size_t i = 0;
    while (i < a.size() && i < b.size()) {
        ++cmp;
        if (a[i] != b[i]) return a[i] < b[i];
        ++i;
    }
    ++cmp;
    return a.size() < b.size();
}
