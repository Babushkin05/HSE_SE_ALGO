#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class TernaryStringQuickSort {
public:
    static void sort(std::vector<std::string>& data, size_t& charComparisons);

private:
    static void sortRecursive(std::vector<std::string>& a, int low, int high, int d, size_t& cmp);
    static char charAt(const std::string& s, int d, size_t& cmp);
};

char TernaryStringQuickSort::charAt(const std::string& s, int d, size_t& cmp) {
    ++cmp;
    if (d < s.size()) return s[d];
    return -1;  // конец строки
}

void TernaryStringQuickSort::sort(std::vector<std::string>& data, size_t& charComparisons) {
    charComparisons = 0;
    sortRecursive(data, 0, static_cast<int>(data.size()) - 1, 0, charComparisons);
}

void TernaryStringQuickSort::sortRecursive(std::vector<std::string>& a, int low, int high, int d, size_t& cmp) {
    if (high <= low) return;

    int lt = low, gt = high;
    char v = charAt(a[low], d, cmp);
    int i = low + 1;

    while (i <= gt) {
        char t = charAt(a[i], d, cmp);
        if (t < v) std::swap(a[lt++], a[i++]);
        else if (t > v) std::swap(a[i], a[gt--]);
        else i++;
    }

    sortRecursive(a, low, lt - 1, d, cmp);
    if (v >= 0) sortRecursive(a, lt, gt, d + 1, cmp);
    sortRecursive(a, gt + 1, high, d, cmp);
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
    TernaryStringQuickSort::sort(data, comparisons);

    for (const auto& str : data) {
        std::cout << str << '\n';
    }

    return 0;
}
