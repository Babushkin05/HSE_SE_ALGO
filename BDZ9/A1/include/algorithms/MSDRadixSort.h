#ifndef MSDRADIXSORT_H
#define MSDRADIXSORT_H

#include <vector>
#include <string>

class MSDRadixSort {
public:
    static void sort(std::vector<std::string>& data, size_t& charComparisons);

private:
    static const int R = 256; // ASCII alphabet size

    static void msdSort(std::vector<std::string>& data, int low, int high, int d, size_t& cmp, std::vector<std::string>& aux);
    static int charAt(const std::string& s, int d, size_t& cmp);
};

#endif // MSDRADIXSORT_H
