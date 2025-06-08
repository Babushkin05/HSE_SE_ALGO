#include <iostream>
#include <vector>

using ll = long long;
const ll MOD = 1'000'000'179;

std::vector<std::vector<ll>> multiplyMatrices(const std::vector<std::vector<ll>>& A, const std::vector<std::vector<ll>>& B) {
    size_t n = A.size();
    size_t m = A[0].size();
    size_t p = B[0].size();
    std::vector<std::vector<ll>> C(n, std::vector<ll>(p, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t k = 0; k < m; ++k) {
            if (A[i][k] == 0) continue; 
            for (size_t j = 0; j < p; ++j) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

std::vector<std::vector<ll>> identityMatrix(size_t n) {
    std::vector<std::vector<ll>> I(n, std::vector<ll>(n, 0));
    for (size_t i = 0; i < n; ++i) {
        I[i][i] = 1;
    }
    return I;
}

std::vector<std::vector<ll>> matrixPower(std::vector<std::vector<ll>> base, ll exponent) {
    std::vector<std::vector<ll>> result = identityMatrix(base.size());
    while (exponent > 0) {
        if (exponent & 1) {
            result = multiplyMatrices(result, base);
        }
        base = multiplyMatrices(base, base);
        exponent >>= 1;
    }
    return result;
}

std::vector<ll> multiplyMatrixVector(const std::vector<std::vector<ll>>& matrix, const std::vector<ll>& vec) {
    size_t n = matrix.size();
    size_t m = matrix[0].size();
    std::vector<ll> res(n, 0);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            res[i] = (res[i] + matrix[i][j] * vec[j]) % MOD;
        }
    }
    return res;
}

int main() {
    ll n; 
    int k;
    std::cin >> n >> k;

    int size = 2 * k;
    std::vector<std::vector<ll>> M(size, std::vector<ll>(size, 0));

    for (int i = 0; i < size; ++i) {
        int height_i = i % k + 1;
        int dir_i = i / k;
        for (int j = 0; j < size; ++j) {
            int height_j = j % k + 1;
            int dir_j = j / k;

            if (dir_i == 1 && dir_j == 0 && height_j > height_i) {
                M[i][j] = 1;
            } else if (dir_i == 0 && dir_j == 1 && height_j < height_i) {
                M[i][j] = 1;
            }
        }
    }

    std::vector<ll> initialVector(size, 1);

    if (n == 1) {
        std::cout << k % MOD << "\n";
        return 0;
    }

    std::vector<ll> v = multiplyMatrixVector(M, initialVector);

    std::vector<std::vector<ll>> M_pow = matrixPower(M, n - 2);
    std::vector<ll> finalVector = multiplyMatrixVector(M_pow, v);

    ll answer = 0;
    for (ll val : finalVector) {
        answer = (answer + val) % MOD;
    }

    std::cout << answer << "\n";
    return 0;
}
