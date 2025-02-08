#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

int estimate(std::vector<int> &v) {
  std::vector<int> main_d(v.size() * 2, 0);
  std::vector<int> sub_d(v.size() * 2, 0);
  int ans = 0;

  for (size_t i = 0; i < v.size(); ++i) {
    ++main_d[v.size() + i - v[i]];
    ++sub_d[i + v[i]];
    if (main_d[v.size() + i - v[i]] > 1 || sub_d[i + v[i]] > 1) {
      continue;
    }
    ++ans;
  }
  return ans;
}
int main() {
  int n;
  std::cin >> n;
  std::vector<int> spots(n);
  for (size_t i = 0; i < n; ++i) {
    spots[i] = i;
  }
  std::random_device random_dev;
  std::mt19937 generator(random_dev());
  std::uniform_int_distribution<> distr(0, n - 1);
  std::shuffle(std::begin(spots), std::end(spots), generator);

  std::uniform_real_distribution<double> rnd(0, 1);

  int energy = estimate(spots);
  double Ti = 1.0;
  for (size_t i = 0; i < 50000; ++i) {
    Ti *= 0.99;
    std::vector<int> new_spots{spots};
    std::swap(new_spots[distr(generator)], new_spots[distr(generator)]);
    int new_energy = estimate(new_spots);
    int dE = new_energy - energy;
    if (exp(dE / Ti) > rnd(generator) || dE > 1) {
      energy = new_energy;
      spots = new_spots;
    }
  }

  for (size_t i = 0; i < n; ++i) {
    std::cout << spots[i] + 1 << ' ';
  }
  return 0;
}

\
