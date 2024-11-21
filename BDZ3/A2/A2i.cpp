#include <algorithm>
#include <iostream>
#include <vector>



void merge(int l, int r, std::vector<int> &v) {
  int m = (l + r) / 2;
  int n1 = m - l;
  int n2 = r - m;
  std::vector<int> v1(n1), v2(n2);

  for (int i = 0; i < n1; ++i)
    v1[i] = v[l + i];
  for (int j = 0; j < n2; ++j)
    v2[j] = v[m + j];

  int i = 0;
  int j = 0;
  int k = l;
  while (i < n1 && j < n2) {
    if (v1[i] <= v2[j]) {
      v[k] = v1[i];
      ++i;
    } else {
      v[k] = v2[j];
      ++j;
    }
    ++k;
  }
  while (i < n1) {
    v[k] = v1[i];
    ++i;
    ++k;
  }
  while (j < n2) {
    v[k] = v2[j];
    ++j;
    ++k;
  }
}

void insertion_sort(int l, int r, std::vector<int> &v) {
  for (size_t i = l; i < r; ++i) {
    int k = v[i];
    int j = i - 1;
    while (j >= l && v[j] > k) {
      v[j + 1] = v[j];
      --j;
    }
    v[j + 1] = k;
  }
}

void merge_sort(int l, int r, std::vector<int> &v) {
  if (l + 1 >= r) {
    return;
  }
  if (r - l <= 15) {
    insertion_sort(l, r, v);
    return;
  }
  int m = (l + r) / 2;
  merge_sort(l, m, v);
  merge_sort(m, r, v);
  merge(l, r, v);
  return;
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
  merge_sort(0, n, v);
  for (size_t i = 0; i < n; ++i) {
    std::cout << v[i] << ' ';
  }
}