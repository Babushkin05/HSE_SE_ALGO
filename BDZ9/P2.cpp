#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::getline(std::cin, input);

    std::unordered_map<std::string, int> dict;
    for (int i = 0; i < 128; ++i) {
        dict[std::string(1, char(i))] = i;
    }

    int dictSize = 128;
    std::vector<int> output;

    std::string w;
    for (char c : input) {
        std::string wc = w + c;
        if (dict.count(wc)) {
            w = wc;
        } else {
            output.push_back(dict[w]);
            dict[wc] = dictSize++;
            w = std::string(1, c);
        }
    }

    if (!w.empty()) {
        output.push_back(dict[w]);
    }

    std::cout << output.size() << "\n";
    for (int i = 0; i < output.size(); ++i) {
        std::cout << output[i];
        if (i + 1 < output.size()) std::cout << " ";
    }
    std::cout << "\n";

    return 0;
}
