#include <iostream>
#include <vector>

std::vector<int> radixSort(std::vector<int> A) {
  int minn = INT_MAX;
  for (size_t i = 0; i < A.size(); ++i) {
    minn = std::min(minn, A[i]);
  }
  for (size_t i = 0; i < A.size(); ++i) {
    A[i] -= minn;
  }

  for (size_t iter = 0; iter < 4; ++iter) {
    std::vector<std::vector<int>> v(256);
    for (size_t i = 0; i < A.size(); ++i) {
      int tmp = A[i];
      for (size_t j = 0; j < iter; ++j) {
        tmp /= 256;
      }
      v[tmp % 256].push_back(A[i]);
    }
    int ind = 0;
    for (size_t i = 0; i < 256; ++i) {
      for (size_t j = 0; j < v[i].size(); ++j) {
        A[ind] = v[i][j];
        ++ind;
      }
    }
  }
  std::vector<int> ans;
  for (size_t i = 0; i < A.size(); ++i) {
    ans.push_back(A[i] + minn);
  }
  return ans;
}

int main() {
  // Отключить синхронизацию между iostream и stdio.
  std::ios::sync_with_stdio(false);
  // Отключить синхронизацию между std::cin и std::cout.
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> v[i];
  }

  std::vector<int> ans = radixSort(v);
  for (size_t i = 0; i < n; ++i) {
    std::cout << ans[i] << ' ';
  }
}