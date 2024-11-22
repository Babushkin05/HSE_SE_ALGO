#include <cmath>
#include <iostream>
#include <vector>
// #include "ArrayGenerator.cpp"

void sink_down(std::vector<int> &arr, int ind, int right) {
  while (2 * ind + 1 <= right) {
    int j = 2 * ind;
    if ((j + 1 < right) && (arr[j] < arr[j + 1]))
      ++j;
    if (!(arr[ind] < arr[j]))
      break;
    std::swap(arr[ind], arr[j]);
    ind = j;
  }
}

void build_max_heap(std::vector<int> &arr, int left, int right) {
  for (size_t k = (right + left) / 2; k >= left; --k) {
    sink_down(arr, k, right);
  }
}

void heap_sort(std::vector<int> &arr, int left, int right) {
  build_max_heap(arr, left, right);

  int last_ind = right;
  for (size_t i = last_ind - 1; i >= left; --i) {
    std::swap(arr[i], arr[1]);
    --last_ind;
    sink_down(arr, 1, last_ind);
  }
}

int partition(std::vector<int> &arr, int left, int right) {
  int pivot = left;
  ++left;
  --right;
  while (left <= right) {
    if (arr[left] < arr[pivot]) {
      ++left;
      continue;
    }
    if (arr[right] >= arr[pivot]) {
      --right;
      continue;
    }
    if (arr[right] < arr[left]) {
      std::swap(arr[left], arr[right]);
      continue;
    }
  }
  std::swap(arr[right], arr[pivot]);
  return right;
}

void insertion_sort(std::vector<int> &arr, int left, int right) {
  for (size_t i = left; i < right; ++i) {
    int k = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > k) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = k;
  }
}

void quick_sort(std::vector<int> &arr, int left, int right, int height,
                int max_height, int threshold = 16) {
  if (height == max_height) {
    heap_sort(arr, 1, arr.size());
    return;
  }
  if (right - left <= threshold) {
    insertion_sort(arr, left, right);
    return;
  }
  if (left < right) {
    int pivot = partition(arr, left, right);
    quick_sort(arr, left, pivot, height + 1, max_height);
    quick_sort(arr, pivot + 1, right, height + 1, max_height);
  }
}

void intro_sort(std::vector<int> &arr) {
  quick_sort(arr, 1, arr.size(), 0, 2 * log2(arr.size()));
}

int main() {
  // Отключить синхронизацию между iostream и stdio.
  std::ios::sync_with_stdio(false);
  // Отключить синхронизацию между std::cin и std::cout.
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> v(n + 1);
  for (size_t i = 1; i <= n; ++i) {
    std::cin >> v[i];
  }
  intro_sort(v);
  for (size_t i = 1; i <= n; ++i) {
    std::cout << v[i] << ' ';
  }

  return 0;
}