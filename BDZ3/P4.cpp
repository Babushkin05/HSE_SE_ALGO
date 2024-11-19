#include <iostream>
#include <string>
#include <vector>

class Fraction {
public:
  int p;
  int q;
  Fraction() : p(0), q(1) {}
  Fraction(int _p, int _q) : p(_p), q(_q) {}
  bool operator<=(const Fraction &rhs) const {
    return static_cast<long double>(p) / q <= static_cast<long double>(rhs.p) / rhs.q;
  }
};

std::istream &operator>>(std::istream &stream, Fraction &f) {
  std::string tmp;
  stream >> tmp;
  size_t ind = tmp.find("/");
  int p = std::stoi(tmp.substr(0, ind));
  int q = std::stoi(tmp.substr(ind + 1));
  f = Fraction{p, q};
  return stream;
}

std::ostream &operator<<(std::ostream &stream, Fraction &f) {
  stream << f.p << '/' << f.q;
  return stream;
}

std::vector<Fraction> v;

void merge(int l, int r) {
  int m = (l + r) / 2;
  int n1 = m - l;
  int n2 = r - m;
  std::vector<Fraction> v1(n1, Fraction{0, 1}), v2(n2, Fraction{0, 1});

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

void merge_sort(int l, int r) {
  if (l + 1 >= r) {
    return;
  }
  int m = (l + r) / 2;
  merge_sort(l, m);
  merge_sort(m, r);
  merge(l, r);
  return;
}

int main() {
  // Отключить синхронизацию между iostream и stdio.
  std::ios::sync_with_stdio(false);
  // Отключить синхронизацию между std::cin и std::cout.
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  v.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    Fraction a;
    std::cin >> a;
    v.push_back(a);
  }
  merge_sort(0, n);
  for (size_t i = 0; i < n; ++i) {
    std::cout << v[i] << ' ';
  }
}