#include <iostream>
#include <vector>
#include <string>

std::vector<int> compute_prefix_function(const std::string& s) {
    int n = s.size();
    std::vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

int main() {
    std::string p;
    std::cin >> p;
    int n = p.size();
    std::vector<int> pi = compute_prefix_function(p);
    int candidate = n - pi[n - 1];
    if (pi[n - 1] >= candidate && n % candidate == 0) {
        std::cout << candidate << '\n';
    } else {
        std::cout << candidate << '\n';
    }
    return 0;
}