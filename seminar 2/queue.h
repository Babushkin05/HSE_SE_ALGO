#include "stack.cpp"
#include <utility>

class Queue {
public:
  void push(int elem);
  int pop();
  int &front();
  int &back();
  int currentMin();

private:
  Stack<std::pair<int, int> > pushStack_;
  Stack<std::pair<int, int> > popStack_;
  void toPop_();
};