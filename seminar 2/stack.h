#include <vector>

template <typename T>
class Stack {
public:
  T pop();
  void push(T elem);
  T &top();
  T &bottom();
  bool empty();
private:
  std::vector<T> data_;
};