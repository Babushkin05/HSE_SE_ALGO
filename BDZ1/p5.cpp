#include <deque>
#include <iostream>
#include <stack>
#include <vector>

int main() {

  std::ios::sync_with_stdio(false); // Отключить синхронизацию между iostream и stdio.
  std::cin.tie(nullptr); // Отключить синхронизацию между std::cin и std::cout

  std::deque<int> front;
  std::deque<int> back;

  int times;
  std::cin >> times;

  while(times--) {

    char c;
    std::cin >> c;

    if (c == '+') {
      int n;
      std::cin >> n;
      back.push_back(n);

    } else if (c == '*') {
      int n;
      std::cin >> n;
      back.push_front(n);

    } else if (c == '-') {

      if (!front.empty()) {
        std::cout << front.front() << '\n';
        front.pop_front();

      } else {
        std::cout << back.front() << '\n';
        back.pop_front();
      }
    }

    if (front.size() < back.size()) {
      front.push_back(back.front());
      back.pop_front();
    }
  }
  
  return 0;
}