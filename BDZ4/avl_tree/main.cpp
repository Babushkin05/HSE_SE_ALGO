#include <iostream>
#include "avl_tree.cpp"

int main(){
    AVLTree *tree = new AVLTree{1};
    int * tmp = tree->find(1);
    std::cout<<tmp;
    delete tree;
}