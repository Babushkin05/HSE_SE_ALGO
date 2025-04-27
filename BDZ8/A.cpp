#include <vector>
#include <string>
#include <iostream>

std::vector<int> compute_prefix_function(const std::string& s) {
    int n = s.length();
    std::vector<int> pi(n);
    
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
    std::string s;
    std::cin>>s;
    std::vector<int> pi = compute_prefix_function(s);
    
    for (int val : pi) {
        std::cout << val << " ";
    }
    
    return 0;
}