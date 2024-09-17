#include "stack.h"

template <typename T>
void Stack<T>::push(T elem){
    this->data_.push_back(elem);
}

template <typename T>
T Stack<T>::pop(){
    T tmp = this->data_.back();
    this->data_.pop_back();
    return tmp;
}

template <typename T>
T& Stack<T>::top(){
    return this->data_.back();
}

template <typename T>
T& Stack<T>::bottom(){
    return this->data_.front();
}

template <typename T>
bool Stack<T>::empty(){
    return this->data_.empty();
}