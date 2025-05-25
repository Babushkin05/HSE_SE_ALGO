#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int k;
    std::cin >> k;
    std::vector<int> codes(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> codes[i];
    }

    std::unordered_map<int, std::string> dict;
    for (int i = 0; i < 128; ++i) {
        dict[i] = std::string(1, char(i));
    }

    int dictSize = 128;
    std::string result;

    std::string prev = dict[codes[0]];
    result += prev;

    for (int i = 1; i < k; ++i) {
        int code = codes[i];
        std::string entry;

        if (dict.count(code)) {
            entry = dict[code];
        } else {
            entry = prev + prev[0];
        }

        result += entry;

        dict[dictSize++] = prev + entry[0];
        prev = entry;
    }

    std::cout << result << "\n";

    return 0;
}
