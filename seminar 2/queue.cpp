#include <stack>
#include "queue.h"

void Queue::toPop_(){
    if(this->popStack_.empty()){
        while(!this->pushStack_.empty()){
            int tmp = this->pushStack_.top();
            this->pushStack_.pop();
            this->popStack_.push(tmp);
            if(!this->pushStack_.empty()){
                this->min_ = std::min(this->min_, tmp);
            }
        }
    }
}

void Queue::toPush_(){
    if(this->pushStack_.empty()){
        while(!this->popStack_.empty()){
            int tmp = this->popStack_.top();
            this->popStack_.pop();
            this->pushStack_.push(tmp);
            this->min_ = std::min(this->min_, tmp);
        }
    }
}


void Queue::push(int elem){
    this->toPush_();
    this->pushStack_.push(elem);
    this->min_ = std::min(this->min_, elem);
}

int Queue::pop() {
    this->toPop_();
    int tmp = this->popStack_.top();
    this->popStack_.pop();
    return tmp;
}

int& Queue::front() {

}

