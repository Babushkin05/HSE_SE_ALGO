#include <cmath>
#include <iostream>
#include <random>

bool is_point_inside_intersection(long double x, long double y, long double x1,
                                  long double y1, long double r1,
                                  long double x2, long double y2,
                                  long double r2, long double x3,
                                  long double y3, long double r3) {
  return pow(x - x1, 2) + pow(y - y1, 2) <= pow(r1, 2) &&
         pow(x - x2, 2) + pow(y - y2, 2) < pow(r2, 2) &&
         pow(x - x3, 2) + pow(y - y3, 2) < pow(r3, 2);
}

int main() {
  long double x1, y1, r1;
  long double x2, y2, r2;
  long double x3, y3, r3;
  std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 >> x3 >> y3 >> r3;

  long double max_x = std::max(std::max(x1 + r1, x2 + r2), x3 + r3);
  long double min_x = std::min(std::min(x1 - r1, x2 - r2), x3 - r3);
  long double max_y = std::max(std::max(y1 + r1, y2 + r2), y3 + r3);
  long double min_y = std::min(std::min(y1 - r1, y2 - r2), y3 - r3);
  std::random_device random_dev;
  std::mt19937 generator(random_dev());
  std::uniform_real_distribution<long double> rndx(min_x, max_x);
  std::uniform_real_distribution<long double> rndy(min_y, max_y);

  size_t n = 0;
  size_t m = 5000000;

  for (size_t iteration = 0; iteration < m; ++iteration) {
    long double x = rndx(generator);
    long double y = rndy(generator);

    n += is_point_inside_intersection(x, y, x1, y1, r1, x2, y2, r2, x3, y3, r3);
  }

  std::cout << (n * (max_x - min_x) * (max_y - min_y)) / m;
}