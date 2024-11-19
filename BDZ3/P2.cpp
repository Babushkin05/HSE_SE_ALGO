#include <iostream>
#include <vector>

std::vector<int> countingSort(std::vector<int> &A) {
  int maxx = INT_MIN;
  int minn = INT_MAX;

  for (size_t i = 0; i < A.size(); ++i) {
    maxx = std::max(maxx, A[i]);
    minn = std::min(minn, A[i]);
  }

  std::vector<int> data(maxx - minn + 1, 0);

  for (size_t i = 0; i < A.size(); ++i) {
    ++data[A[i] - minn];
  }

  std::vector<int> ans;
  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data[i]; ++j) {
      ans.push_back(minn + i);
    }
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

  std::vector<int> ans = countingSort(v);
  for (size_t i = 0; i < n; ++i) {
    std::cout << ans[i] << ' ';
  }
}