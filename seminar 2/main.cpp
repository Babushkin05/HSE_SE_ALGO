#include "queue.cpp"
#include <iostream>

int main() {
  Queue a;
  a.push(14);
  a.push(2);
  std::cout << a.currentMin() << '\n';
  a.push(32);
  a.push(5);
  a.push(28);

  std::cout << a.currentMin() << ' ' << a.pop() << '\n';
  a.pop();
  std::cout << a.back()<<' '<<a.currentMin();
}