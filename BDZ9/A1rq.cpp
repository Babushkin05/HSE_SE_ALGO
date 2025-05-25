#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class MSDRadixSortWithQuick {
public:
    static void sort(std::vector<std::string>& data, size_t& charComparisons);

private:
    static const int R = 256;      // ASCII alphabet size
    static const int CUTOFF = 16;  // Switch to QuickSort when subarray size <= CUTOFF

    static void msdSort(std::vector<std::string>& data, int low, int high, int d, size_t& cmp, std::vector<std::string>& aux);
    static void quickSort(std::vector<std::string>& data, int low, int high, int d, size_t& cmp);
    static int charAt(const std::string& s, int d, size_t& cmp);
};

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

int main() {
    int n;
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::string> data(n);
    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, data[i]);
    }

    size_t comparisons = 0;
    MSDRadixSortWithQuick::sort(data, comparisons);

    for (const auto& str : data) {
        std::cout << str << '\n';
    }

    return 0;
}
