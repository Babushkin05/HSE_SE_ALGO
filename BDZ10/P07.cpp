#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int l, n;
    std::cin >> l >> n;

    std::vector<int> cuts(n + 2);
    cuts[0] = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> cuts[i];
    }
    cuts[n + 1] = l;

    int size = n + 2;
    std::vector<std::vector<int>> dp(size, std::vector<int>(size, 0));

    for (int len = 2; len < size; ++len) {
        for (int i = 0; i + len < size; ++i) {
            int j = i + len;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; ++k) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] - cuts[i]);
            }
        }
    }

    std::cout << dp[0][size - 1] << "\n";
    return 0;
}
