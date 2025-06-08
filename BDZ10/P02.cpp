#include <iostream>
#include <vector>

int main() {
    int n, l, r;
    std::cin >> n >> l >> r;

    std::vector<int> result(n, 0);
    int len = r - l + 1;
    int center = (l + r) / 2; 

    int left = center;
    int right = center;
    bool toRight = true;
    int pos;
    int i = n;

    while (left >= 1 && right <= n) {
        if (toRight) {
            pos = right;
            ++right;
        } else {
            pos = left;
            --left;
        }
        result[pos - 1] = i;
        --i;
        toRight = !toRight;
    }

    for (int j = left; j >= 1; --j) {
        result[j - 1] = i;
        --i;
    }

    for (int j = right; j <= n; ++j) {
        result[j - 1] = i;
        --i;
    }

    for (int j = 0; j < n; ++j) {
        std::cout << result[j] + 1 << " ";
    }
    std::cout << "\n";

    return 0;
}
