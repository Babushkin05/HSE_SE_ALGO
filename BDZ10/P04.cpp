#include <iostream>

const int MOD = 1000000007;

int main() {
    int N;
    std::cin >> N;

    long long dpA = 1; 
    long long dpB = 1; 

    for (int i = 2; i <= N; ++i) {
        long long newA = (dpA + dpB) % MOD;
        long long newB = dpA % MOD;

        dpA = newA;
        dpB = newB;
    }

    long long result = (dpA + dpB) % MOD;
    std::cout << result << std::endl;

    return 0;
}
