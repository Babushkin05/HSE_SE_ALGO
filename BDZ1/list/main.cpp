#include <iostream>
#include "release.cpp"

int main(){
    
    List l{};
    l.push_back(3);
    l.push_back(4);
    l.push_back(6);
    l.push_back(3);
    l.push_back(5);
    l.push_back(6);

    Node* tmp = l.head;
    for(size_t i = 0; i< l.size();++i){
        std::cout<<tmp->value<<'\n';
        tmp = tmp->next;
    }
    std::cout<<'\n';
    l.remove_duplicates();
    tmp = l.head;
    for(size_t i = 0; i< l.size();++i){
        std::cout<<tmp->value<<'\n';
        tmp = tmp->next;
    }

    return 0;
}