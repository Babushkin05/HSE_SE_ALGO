#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char ch, int freq, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr)
        : ch(ch), freq(freq), left(left), right(right) {}
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::getline(std::cin, s);

    if (s.empty()) {
        std::cout << "0 0\n";
        return 0;
    }

    std::unordered_map<char, int> freq;
    for (char ch : s)
        freq[ch]++;

    auto comp = [](HuffmanNode* a, HuffmanNode* b) { return a->freq > b->freq; };
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, decltype(comp)> pq(comp);

    for (auto& pair : freq)
        pq.push(new HuffmanNode(pair.first, pair.second));

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        pq.push(new HuffmanNode('\0', left->freq + right->freq, left, right));
    }

    std::unordered_map<char, std::string> huffmanCode;
    auto root = pq.top();

    std::function<void(HuffmanNode*, std::string)> generateCodes = [&](HuffmanNode* node, std::string code) {
        if (!node) return;
        if (!node->left && !node->right) {
            huffmanCode[node->ch] = code;
            return;
        }
        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    };

    if (freq.size() == 1) {
        huffmanCode[root->ch] = "0";
    } else {
        generateCodes(root, "");
    }

    size_t encodedLength = 0;
    for (auto& pair : freq)
        encodedLength += pair.second * huffmanCode[pair.first].length();

    std::cout << huffmanCode.size() << " " << encodedLength << "\n";

    std::vector<std::pair<char, std::string>> sortedCodes(huffmanCode.begin(), huffmanCode.end());
    std::sort(sortedCodes.begin(), sortedCodes.end());

    for (auto& pair : sortedCodes)
        std::cout << pair.first << ": " << pair.second << "\n";

    for (char ch : s)
        std::cout << huffmanCode[ch];
    std::cout << "\n";

    return 0;
}
