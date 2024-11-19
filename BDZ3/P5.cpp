#include <cmath>
#include <iostream>
#include <random>

std::string random_vec(int n) {
  std::random_device random_dev;
  std::mt19937 generator(random_dev());
  std::uniform_int_distribution<> distr(0, 16);
  std::string vec = "";
  for (size_t i = 0; i < n; ++i) {
    int rnd = distr(generator);
    if (rnd < 10) {
      vec += '0' + rnd;
    } else {
      vec += 'A' + rnd - 10;
    }
  }
  // for(int i = 0; i<vec.size();++i){
  //   std::cout<<vec[i];
  // }std::cout<<'\n';
  return vec;
}

bool boolean_and(char c1, char c2) {
  int n1;
  int n2;
  if (c1 <= '9') {
    n1 = c1 - '0';
  } else {
    n1 = c1 - 'A' + 10;
  }
  if (c2 <= '9') {
    n2 = c2 - '0';
  } else {
    n2 = c2 - 'A' + 10;
  }

  int res = n1 & n2;
  bool ans = false;
  while (res > 0) {
    ans = ans != (res % 2);
    res /= 2;
  }
  return ans;
}
bool boolean_and(std::string &s1, std::string &s2) {
  bool res = false;
  for (size_t i = 0; i < s1.size(); ++i) {
    res = res != boolean_and(s1[i], s2[i]);
    // std::cout<<s1[i]<<' '<<s2[i]<<' '<<res<<'\n';
  }
  return res;
}

std::vector<bool> boolean_and(std::vector<std::string> &v, std::string &s) {
  std::vector<bool> res;
  for (size_t i = 0; i < v.size(); ++i) {
    res.push_back(boolean_and(v[i], s));
  }
  return res;
}

std::string to_string_vec(std::vector<bool> &v) {
  std::string res = "";
  int tmp = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    if (i % 4 == 0 && i != 0) {
      if (tmp >= 10) {
        res += tmp + 'A' - 10;
      } else {
        res += tmp + '0';
      }
      tmp = 0;
    }
    tmp = 2 * tmp + v[i];
  }
  if (v.size() % 4 != 0) {
    tmp *= pow(2, 4 - (v.size() % 4));
  }
  if (tmp >= 10) {
    res += tmp + 'A' - 10;
  } else {
    res += tmp + '0';
  }
  return res;
}

bool is_eq(std::vector<bool> &v1, std::vector<bool> &v2) {
  bool f = 1;
  for (size_t i = 0; i < v1.size(); ++i) {
    f &= (v1[i] == v2[i]);
    // std::cout<<v1[i]<<' ';
  } // std::cout<<'\n';
  return f;
}

int main() {
  // Отключить синхронизацию между iostream и stdio.
  std::ios::sync_with_stdio(false);
  // Отключить синхронизацию между std::cin и std::cout.
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<std::string> a(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  std::vector<std::string> b(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> b[i];
  }
  std::vector<std::string> c(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> c[i];
  }
  bool f = 1;
  for (size_t iter = 0; iter < 10; ++iter) {
    std::string r = random_vec((n + 3) / 4);
    std::vector<bool> v1 = boolean_and(b, r);
    std::vector<bool> v2 = boolean_and(c, r);
    r = to_string_vec(v1);
    v1 = boolean_and(a, r);
    f &= is_eq(v1, v2);
  }
  if (f) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}