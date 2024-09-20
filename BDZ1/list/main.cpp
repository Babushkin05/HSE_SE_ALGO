#include <iostream>
#include "release.cpp"

int main(){
    std::vector<int> v{1,2,3,4,5};
    List a{v};
    Node* tmp = a.head;
    for(size_t i = 0; i< a.size()-1;++i){
        std::cout<<tmp->value<<'\n';
        tmp = tmp->next;
    }
    List b{a};
    a.clear();
    return 0;
}