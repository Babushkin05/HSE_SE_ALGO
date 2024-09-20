#include <stdexcept>
#include <set>
#include "list.h"

List::List()  {
    head = tail = nullptr;
    _size = 0;
}

List::List(const List& other) : head{nullptr}, tail{nullptr}, _size{0}{
    if(other.empty()){
        return;
    }
    Node* tmp;
    tmp = other.head;
    Node* head_ = new Node(other.head->value);
    head = tail = head_;
    ++_size;
    for(size_t i = 1;i < other.size();++i){
        push_back(tmp->next->value);
        tmp = tmp->next;
    }
}

List::List(std::vector<int> array) : head{nullptr}, tail{nullptr}, _size(0) {
    if(array.size() == 0){
        return;
    }
    for(size_t i = 0; i < array.size(); ++i ){
        push_back(array[i]);
    }
}

List::~List() = default;

int List::front() {
    return head->value;
}


int List::back() {
    return tail->value;
}

void List::push_back(int value) {
    Node* tmp = new Node{tail, nullptr, value};
    if(_size == 0){
        head = tail = tmp;
    }
    else{
        tail->next = tmp;
        tail = tmp;
    }
    ++_size;
}

void List::push_front(int value) {
    Node* tmp = new Node{nullptr, head, value};
    if(_size == 0){
        head = tail = tmp;
    }
    else{
        head->prev = tmp;
        head = tmp;
    }
    ++_size;
}

void List::insert(Node* pos, int value) {
    if(pos == nullptr || (pos->next == nullptr && pos->prev == nullptr && pos != head))
        throw std::runtime_error("Incorrect position!");
    if(pos->next == nullptr)
        push_back(value);
    else{
        Node* tmp = new Node{pos,pos->next,value};
        pos->next = tmp;
        if(tmp->next){
            (tmp->next)->prev = tmp;
        }
        ++_size;
    }
}

void List::pop_front() {
    if(head != nullptr){
        head = head->next;
        if(head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;
        --_size;
    }
    else{
        throw std::runtime_error("Deleting in empty list");
    }
}

void List::pop_back() {
    if(tail != nullptr){
        tail = tail->prev;
        if(tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;
        --_size;
    }
    else{
        throw std::runtime_error("Deleting in empty list");
    }
}

void List::erase(Node* pos) {
    if(pos == nullptr)
        throw std::runtime_error("Incorrect position!");
    if(pos == tail)
        pop_back();
    else if(pos == head)
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
    for(size_t i = 0; i < _size; ++i){
        if(s.count(tmp->value)){
            erase(tmp);
        }
        s.insert(tmp->value);
        tmp = tmp->next;
    }
    if(s.count(tmp->value)){
        erase(tmp);
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
    if(other.empty())
        return;
    if(empty())
        copy(other);
    else{
        tail->next = other.head;
        other.head->prev = tail;
        tail = other.tail;
        _size+=other._size;
    }
}

bool List::check_cycle() const {
    Node* turtle = head;
    Node* rabbit = head;
    while(rabbit != tail){
        if(rabbit == nullptr or rabbit->next == nullptr)
            break;
        turtle = turtle->next;
        rabbit = rabbit->next->next;
        if(rabbit == turtle)
            return true;
    }

    turtle = tail;
    rabbit = tail;
    while(rabbit != head){
        if(rabbit == nullptr or rabbit->prev == nullptr)
            break;
        turtle = turtle->prev;
        rabbit = rabbit->prev->prev;
        if(rabbit == turtle)
            return true;
    }

    return false;
}

size_t List::size() const {
    return _size;
}

bool List::empty() const{
    return _size == 0;
}

void List::copy(const List& other) {
    clear();
    if(other.empty()){
        return;
    }
    Node* tmp;
    tmp = other.head;
    Node* head_ = new Node(other.head->value);
    head = tail = head_;
    ++_size;
    for(size_t i = 1;i < other.size();++i){
        push_back(tmp->next->value);
        tmp = tmp->next;
    }
}
