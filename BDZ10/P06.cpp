#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<int> m(N), c(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> m[i];
    }
    for (int i = 0; i < N; ++i) {
        std::cin >> c[i];
    }

    std::vector<int> dp(M + 1, 0);

    for (int i = 0; i < N; ++i) {
        for (int w = M; w >= m[i]; --w) {
            dp[w] = std::max(dp[w], dp[w - m[i]] + c[i]);
        }
    }

    int answer = 0;
    for (int w = 0; w <= M; ++w) {
        if (dp[w] > answer) {
            answer = dp[w];
        }
    }

    std::cout << answer << "\n";

    return 0;
}
