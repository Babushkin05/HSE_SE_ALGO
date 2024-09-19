#include <stdexcept>
#include <set>
#include "list.h"

List::List() : head{nullptr}, tail{nullptr}, _size{0} {
}

List::List(const List& other) : head{other.head}, tail{other.tail}, _size{other._size}{
}

List::List(std::vector<int> array) : _size(array.size()) {
    Node head_{array[0]};
    head = &head_;
    tail = &head_;
    for(size_t i = 1; i < _size; ++i ){
        push_back(array[i]);
    }
}

List::~List() {
    delete &_size;
    delete head;
    delete tail;
}

int List::front() {
    return head->value;
}


int List::back() {
    return tail->value;
}

void List::push_back(int value) {
    Node tmp{value};
    tmp.next = tail;
    tail->prev = &tmp;
    tail = &tmp;
    ++_size;
}

void List::push_front(int value) {
    Node tmp{value};
    tmp.prev = head;
    head->next = &tmp;
    head = &tmp;
    ++_size;
}

void List::insert(Node* pos, int value) {
    if(pos == nullptr || pos->next == nullptr && pos->prev == nullptr && pos != head)
        throw std::runtime_error("Incorrect position!");
    if(pos->next == nullptr)
        push_back(value);
    else{
        Node tmp{value};
        tmp.next = pos->next;
        tmp.prev = pos;
        pos->next = &tmp;
        ++_size;
    }
}

void List::pop_front() {
    head = head->next;
    head->prev = nullptr;
    --_size;
}

void List::pop_back() {
    tail = tail->prev;
    tail->next = nullptr;
    --_size;
}

void List::erase(Node* pos) {
    if(pos == nullptr || pos->next == nullptr && pos->prev == nullptr && pos != head)
        throw std::runtime_error("Incorrect position!");
    if(pos->next == nullptr)
        pop_back();
    else if(pos->prev == nullptr)
        pop_front();
    else{
        (pos->prev)->next = pos->next;
        (pos->next)->prev = pos->prev;
        --_size;
    }
}

void List::clear() {
    while (_size>0)
    {
        pop_back();
    }
}

void List::reverse() {
    Node* tmp = head;
    for(size_t i = 0; i < _size; ++i){
        std::swap(tmp->next,tmp->prev);
        tmp = tmp->prev;
    }
    std::swap(head,tail);
}

void List::remove_duplicates() {
    std::set<int> s;
    Node* tmp = head;
    s.insert(tmp->value);
    tmp = tmp->next;
    for(size_t i = 0; i < _size - 1; ++i){
        if(s.count(tmp->value)){
            erase(tmp);
        }
        s.insert(tmp->value);
        tmp = tmp->next;
    }
}

void List::replace(int old_value, int new_value) {
    Node* tmp = head;
    for(size_t i = 0; i< _size; ++i){
        if(tmp->value == old_value)
            tmp->value = new_value;
        tmp = tmp->next;
    }
}

void List::merge(const List& other) {
    tail->next = other.head;
    tail = other.tail;
    _size+=other._size;
}

bool List::check_cycle() const {
    Node* turtle = head;
    Node* rabbit = head;
    while(rabbit != tail){
        
    }
}

size_t List::size() const {
    throw std::runtime_error("Not implemented!");
}

bool List::empty() const{
    throw std::runtime_error("Not implemented!");
}

void List::copy(const List& other) {
    throw std::runtime_error("Not implemented!");
}
