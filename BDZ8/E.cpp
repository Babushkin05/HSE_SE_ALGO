#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int levenshtein_distance(const std::string &s1, const std::string &s2) {
    int m = s1.size();
    int n = s2.size();
    
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }
    
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;
            dp[i][j] = std::min({
                dp[i-1][j] + 1,   
                dp[i][j-1] + 1,    
                dp[i-1][j-1] + cost 
            });
        }
    }
    
    return dp[m][n];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    std::cin.ignore(); 
    
    std::vector<int> results;
    results.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        std::string s1, s2;
        std::getline(std::cin, s1);
        std::getline(std::cin, s2);
        
        results.push_back(levenshtein_distance(s1, s2));
    }
    
    for (int i = 0; i < n; ++i) {
        std::cout << results[i];
        if (i != n - 1) {
            std::cout << " ";
        }
    }
    
    return 0;
}