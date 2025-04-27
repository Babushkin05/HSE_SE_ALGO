#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class StringHasher {
public:
  explicit StringHasher(int base = 29, int mod = 1'000'000'007)
      : base_(base), mod_(mod) {}

  void compute_hashes(const std::string &str) {
    const size_t n = str.length();
    hashes_.resize(n + 1);
    powers_.resize(n + 1);

    hashes_[0] = 0;
    powers_[0] = 1;

    for (size_t i = 0; i < n; ++i) {
      hashes_[i + 1] =
          (static_cast<long long>(hashes_[i]) * base_ + (str[i] - 'a')) % mod_;
      powers_[i + 1] = (static_cast<long long>(powers_[i])) * base_ % mod_;
    }
  }

  int get_hash(size_t l, size_t r) const {
    if (l > r || r >= hashes_.size() - 1) {
      throw std::out_of_range("Invalid substring range");
    }
    int hash = (hashes_[r + 1] -
                static_cast<long long>(hashes_[l]) * powers_[r - l + 1] % mod_ +
                mod_) %
               mod_;
    return hash;
  }

private:
  int base_;
  int mod_;
  std::vector<int> hashes_;
  std::vector<int> powers_;
};

class PalindromeCounter {
public:
  explicit PalindromeCounter(const std::string &str) : str_(str) {
    forward_hasher_.compute_hashes(str_);

    std::string reversed_str(str_);
    std::reverse(reversed_str.begin(), reversed_str.end());
    reversed_hasher_.compute_hashes(reversed_str);
  }

  long long count_all_palindromes() {
    const size_t n = str_.length();
    long long total = 0;

    for (size_t center = 0; center < n; ++center) {
      int max_radius = std::min(center, n - 1 - center);
      total += find_max_palindrome_radius(center, center, max_radius);
    }

    for (size_t left_center = 0; left_center < n - 1; ++left_center) {
      int max_radius = std::min(left_center, n - 2 - left_center);
      total +=
          find_max_palindrome_radius(left_center, left_center + 1, max_radius);
    }

    return total;
  }

private:
  int find_max_palindrome_radius(size_t left_center, size_t right_center,
                                 int max_radius) {
    int low = 0, high = max_radius;
    int best = 0;

    while (low <= high) {
      int mid = (low + high) / 2;
      size_t l = left_center - mid;
      size_t r = right_center + mid;

      size_t reversed_l = str_.length() - 1 - r;
      size_t reversed_r = str_.length() - 1 - l;

      if (forward_hasher_.get_hash(l, r) ==
          reversed_hasher_.get_hash(reversed_l, reversed_r)) {
        best = mid + 1;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return best;
  }

  std::string str_;
  StringHasher forward_hasher_;
  StringHasher reversed_hasher_;
};

int main() {
  std::string input;
  std::cin >> input;

  PalindromeCounter counter(input);
  long long result = counter.count_all_palindromes();

  std::cout << result << '\n';
  return 0;
}