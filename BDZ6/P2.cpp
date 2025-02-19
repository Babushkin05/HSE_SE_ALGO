#include <iostream>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

int n, m;
std::vector<std::vector<std::pair<int, int>>> edges;

int main() {
  std::cin >> n >> m;
  edges.resize(n);
  for (size_t i = 0; i < m; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    edges[a - 1].push_back(std::make_pair(-c, b - 1));
    edges[b - 1].push_back(std::make_pair(-c, a - 1));
  }

  std::set<std::pair<int, int>> used;
  std::unordered_set<int> included{0};
  std::priority_queue<std::tuple<int, int, int>> available;
  for (auto [c, a] : edges[0]) {
    available.push(std::make_tuple(c, a, 0));
  }
  int ans = 0;
  while (included.size() < n) {
    auto [c, b, a] = available.top();
    available.pop();
    if (included.contains(b)){
        if(included.contains(a)){
            continue;
        }
        std::swap(a, b);
    }
    included.insert(b);
    used.insert(std::make_pair(std::min(a, b), std::max(a, b)));
    ans -= c;
    for (auto [c1, b1] : edges[b]) {
      available.push(std::make_tuple(c1, b1, b));
    }

  }
  int ans1 = ans;
  int ans2 = INT_MAX;
  for(auto USENT : used){
      std::unordered_set<int> included{0};
      std::priority_queue<std::pair<int, int>> available;
      for (auto p : edges[0]) {
        if (0 != USENT.first || p.second != USENT.second)
          available.push(p);
      }
      if(available.empty())
        continue;
        //std::cout<<USENT.first + 1 <<' '<<USENT.second + 1<<'\n';
      int ans = 0;
      while (included.size() < n) {
        auto [c, a] = available.top();
        available.pop();
        if (included.contains(a))
          continue;
        included.insert(a);
        ans -= c;
        for (auto p : edges[a]) {
          if (std::min(a, p.second) != USENT.first || std::max(a, p.second) != USENT.second)
            available.push(p);
        }
      }
      //std::cout << ans << '\n';
      if (ans < ans1) {
        ans2 = ans1;
        ans1 = ans;
      } else if (ans < ans2) {
        ans2 = ans;
      }
  }
  std::cout << ans1 << ' ' << ans2;
}