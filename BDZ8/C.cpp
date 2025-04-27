#include <iostream>
#include <vector>
#include <string>

std::vector<int> compute_prefix_function(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> pi(m, 0);
    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

std::vector<int> kmp_search(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    if (pattern.empty()) {
        return positions;
    }
    int n = text.size();
    int m = pattern.size();
    std::vector<int> pi = compute_prefix_function(pattern);
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            positions.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return positions;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string P, T;
    std::getline(std::cin, P);
    std::getline(std::cin, T);

    std::vector<int> positions = kmp_search(T, P);

    std::cout << positions.size() << "\n";
    for (int pos : positions) {
        std::cout << pos << "\n";
    }

    return 0;
}