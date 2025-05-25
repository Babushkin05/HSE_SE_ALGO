#include "algorithms/StringMergeSort.h"
#include <algorithm>

std::pair<std::strong_ordering, int> StringMergeSort::lcpCompare(
    const std::string& a, const std::string& b, int k, size_t& cmp) {
    
    for (int i = k; i < std::min(a.size(), b.size()); ++i) {
        ++cmp;
        if (a[i] != b[i]) {
            return {a[i] <=> b[i], i};
        }
    }

    if (a.size() == b.size()) {
        return {std::strong_ordering::equal, static_cast<int>(a.size())};
    }
    return (a.size() < b.size())
        ? std::make_pair(std::strong_ordering::less, static_cast<int>(a.size()))
        : std::make_pair(std::strong_ordering::greater, static_cast<int>(b.size()));
}

std::vector<std::pair<std::string, int>> StringMergeSort::merge(
    std::vector<std::pair<std::string, int>>& left,
    std::vector<std::pair<std::string, int>>& right,
    size_t& cmp) {

    std::vector<std::pair<std::string, int>> result;
    result.reserve(left.size() + right.size());

    auto it_left = left.begin();
    auto it_right = right.begin();

    while (it_left != left.end() && it_right != right.end()) {
        if (it_left->second > it_right->second) {
            result.emplace_back(*it_left);
            ++it_left;
        } else if (it_left->second < it_right->second) {
            result.emplace_back(*it_right);
            ++it_right;
        } else {
            auto [order, lcp] = lcpCompare(it_left->first, it_right->first, it_left->second, cmp);
            if (order == std::strong_ordering::less) {
                result.emplace_back(*it_left);
                ++it_left;
                it_right->second = lcp;
            } else {
                result.emplace_back(*it_right);
                ++it_right;
                it_left->second = lcp;
            }
        }
    }

    while (it_left != left.end()) {
        result.emplace_back(*it_left++);
    }

    while (it_right != right.end()) {
        result.emplace_back(*it_right++);
    }

    return result;
}

std::vector<std::pair<std::string, int>> StringMergeSort::mergeSortHelper(
    std::vector<std::string>::iterator begin,
    std::vector<std::string>::iterator end,
    size_t& cmp) {

    if (std::next(begin) == end) {
        return { {*begin, 0} };
    }

    auto mid = begin + (end - begin) / 2;
    auto left = mergeSortHelper(begin, mid, cmp);
    auto right = mergeSortHelper(mid, end, cmp);

    return merge(left, right, cmp);
}

void StringMergeSort::sort(std::vector<std::string>& data, size_t& charComparisons) {
    charComparisons = 0;
    if (data.size() <= 1) return;

    auto sortedPairs = mergeSortHelper(data.begin(), data.end(), charComparisons);
    data.clear();
    for (const auto& [str, _] : sortedPairs) {
        data.emplace_back(str);
    }
}
