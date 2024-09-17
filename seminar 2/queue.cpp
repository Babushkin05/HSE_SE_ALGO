#include "queue.h"
#include <stack>

void Queue::toPop_() {
  if (this->popStack_.empty()) {
    int minOfPopStack = INT_MAX;
    while (!this->pushStack_.empty()) {
      std::pair<int,int> tmp = this->pushStack_.top();
      this->pushStack_.pop();
      minOfPopStack = std::min(minOfPopStack,tmp.second);
      this->popStack_.push(std::make_pair(tmp.first,minOfPopStack));
    }
  }
}

void Queue::push(int elem) {
  if(this->pushStack_.empty()){
    this->pushStack_.push(std::make_pair(elem,elem));
  }
  else{
    this->pushStack_.push(std::make_pair(elem,std::min(elem,this->pushStack_.top().second)));
  }
}

int Queue::pop() {
  this->toPop_();
  std::pair<int,int> tmp = this->popStack_.top();
  this->popStack_.pop();
  return tmp.first;
}

int &Queue::front() {
  this->toPop_();
  return this->popStack_.top().first;
}

int &Queue::back() {
  if(!this->pushStack_.empty()){
    return this->pushStack_.top().first;
  }
  return this->popStack_.bottom().first;
}

int Queue::currentMin() {
    int popMin = INT_MAX;
    int pushMin = INT_MAX;
    if(!this->popStack_.empty())
        popMin = this->popStack_.top().second;
    if(!this->pushStack_.empty())
        pushMin = this->pushStack_.top().second;
    return std::min(popMin,pushMin); 
}
