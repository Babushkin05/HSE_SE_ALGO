#include <algorithm>
#include <iostream>
#include <vector>

int n = 52, m, num = 1;

void swapper() {
  std::cout << "Swapper " << num++ << ":\n";
  std::vector<int> vec(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  while (m--) {
    int a, l, r;
    std::cin >> a >> l >> r;

    if (a == 1) {
      for (int i = l - 1; i < r; i += 2) {
        std::swap(vec[i], vec[i + 1]);
      }
    } else {
      int sum = 0;
      for (int i = l - 1; i < r; ++i) {
        sum += vec[i];
      }
      std::cout << sum << '\n';
    }
  }
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  while (std::cin >> n >> m) {
    if (n == 0 && m == 0) {
      break;
    }

    swapper();
  }
  return 0;
}