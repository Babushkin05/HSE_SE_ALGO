#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

std::vector<int> boyer_moore_horspool_search(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    int n = text.size();
    int m = pattern.size();
    
    if (m == 0 || n < m) {
        return positions;
    }

    std::unordered_map<char, int> bad_char_shift;
    for (int i = 0; i < m - 1; ++i) {
        bad_char_shift[pattern[i]] = m - 1 - i;
    }

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            --j;
        }
        if (j < 0) {
            positions.push_back(i);
            i += 1;  
        } else {
            char bad_char = text[i + m - 1];
            if (bad_char_shift.find(bad_char) != bad_char_shift.end()) {
                i += bad_char_shift[bad_char];
            } else {
                i += m;
            }
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

    std::vector<int> positions = boyer_moore_horspool_search(T, P);

    std::cout << positions.size() << "\n";
    for (int pos : positions) {
        std::cout << pos << "\n";
    }

    return 0;
}