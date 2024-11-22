#include <algorithm>
#include <random>

class ArrayGenerator {
public:
  static const int max_len = 10000;
  static const int min_len = 20;
  static const int len_step = 100;
  static const int max_a = 0;
  static const int min_a = 6000;

  static std::vector<int> get_random_array() {
    int n = max_len;
    std::vector<int> v(n);
    for (size_t i = 0; i < n; ++i) {
      v[i] = get_random_number(min_a, max_a);
    }
    return v;
  }

  static std::vector<int> get_reverse_sorted_array() {
    std::vector<int> v = get_random_array();
    std::sort(v.rbegin(), v.rend());
    return v;
  }

  static std::vector<int> get_almost_sorted_array() {
    std::vector<int> v = get_random_array();
    std::sort(v.begin(), v.end());
    int k = get_random_number(v.size() / 200, v.size() / 100);
    for (size_t iter = 0; iter < k; ++iter) {
      std::swap(v[iter], v[v.size() - iter - 1]);
    }
    return v;
  }

private:
  static int get_random_number(int l, int r, int step = 1) {
    std::random_device random_dev;
    std::mt19937 generator(random_dev());
    std::uniform_int_distribution<> distr(l, r);
    return (distr(generator) / step) * step;
  }
};