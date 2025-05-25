#ifndef MSDRADIXSORTWITHQUICK_H
#define MSDRADIXSORTWITHQUICK_H

#include <vector>
#include <string>

class MSDRadixSortWithQuick {
public:
    static void sort(std::vector<std::string>& data, size_t& charComparisons);

private:
    static const int R = 256;      // ASCII alphabet size
    static const int CUTOFF = 16;  // Switch to QuickSort when subarray size <= CUTOFF

    static void msdSort(std::vector<std::string>& data, int low, int high, int d, size_t& cmp, std::vector<std::string>& aux);
    static void quickSort(std::vector<std::string>& data, int low, int high, int d, size_t& cmp);
    static int charAt(const std::string& s, int d, size_t& cmp);
    static bool less(const std::string& a, const std::string& b, int d, size_t& cmp);
};

#endif // MSDRADIXSORTWITHQUICK_H
