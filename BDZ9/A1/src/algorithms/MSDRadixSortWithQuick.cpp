#include "algorithms/MSDRadixSortWithQuick.h"
#include <algorithm>

void MSDRadixSortWithQuick::sort(std::vector<std::string>& data, size_t& charComparisons) {
    charComparisons = 0;
    if (data.size() <= 1) return;
    std::vector<std::string> aux(data.size());
    msdSort(data, 0, data.size() - 1, 0, charComparisons, aux);
}

int MSDRadixSortWithQuick::charAt(const std::string& s, int d, size_t& cmp) {
    ++cmp;
    return d < s.size() ? static_cast<unsigned char>(s[d]) : -1; 
}

void MSDRadixSortWithQuick::msdSort(std::vector<std::string>& data, int low, int high, int d, size_t& cmp, std::vector<std::string>& aux) {
    if (high <= low + CUTOFF) {
        quickSort(data, low, high, d, cmp);
        return;
    }

    std::vector<int> count(R + 2, 0); 

    for (int i = low; i <= high; ++i) {
        int c = charAt(data[i], d, cmp);
        count[c + 2]++;
    }

    for (int r = 0; r < R + 1; ++r) {
        count[r + 1] += count[r];
    }

    for (int i = low; i <= high; ++i) {
        int c = charAt(data[i], d, cmp);
        aux[count[c + 1]++] = std::move(data[i]);
    }

    for (int i = low; i <= high; ++i) {
        data[i] = std::move(aux[i - low]);
    }

    for (int r = 0; r < R; ++r) {
        msdSort(data, low + count[r], low + count[r + 1] - 1, d + 1, cmp, aux);
    }
}

void MSDRadixSortWithQuick::quickSort(std::vector<std::string>& data, int low, int high, int d, size_t& cmp) {
    if (low >= high) return;

    int lt = low, gt = high;
    int v = charAt(data[low], d, cmp);
    int i = low + 1;

    while (i <= gt) {
        int t = charAt(data[i], d, cmp);
        if (t < v) std::swap(data[lt++], data[i++]);
        else if (t > v) std::swap(data[i], data[gt--]);
        else i++;
    }

    quickSort(data, low, lt - 1, d, cmp);
    if (v >= 0) quickSort(data, lt, gt, d + 1, cmp);
    quickSort(data, gt + 1, high, d, cmp);
}
