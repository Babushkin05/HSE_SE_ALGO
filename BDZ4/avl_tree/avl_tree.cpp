#include "avl_tree.h"
#include <algorithm>

Node::Node(int value) {
    height = 0;
    left = nullptr;
    right = nullptr;
    value = value;
}

Node::~Node() = default;

AVLTree::AVLTree() {
    root_ = nullptr;
    size_ = 0;
}

AVLTree::AVLTree(int value) {
    Node r{value};
    root_ = &r;
    size_ = 1;
}

int AVLTree::getHeight() {
    return getNodeHeight(root_);
}

void AVLTree::insert(int value) {
    insertNode(root_, value);
}

void AVLTree::erase(int value) {
    removeNode(root_, value);
}

int *AVLTree::find(int value) {
    return &findNode(root_, value)->value;
}

int *AVLTree::traversal() {
    int arr[size_];
    traversalInternal(root_, arr, 0);
    return arr;
}

int *AVLTree::lowerBound(int value) {
    return &lowerBoundInternal(root_, value)->value;
}

bool AVLTree::empty() {
    return size_ == 0;
}

Node *AVLTree::getRoot() {
    return root_;
}

int AVLTree::getSize() {
    return size_;
}

AVLTree::~AVLTree() {
    removeMinNode(root_);
}

int AVLTree::getNodeHeight(Node *node) {
    if(node == nullptr){
        return -1;
    }
    return node->height;
}

int AVLTree::balanceFactor(Node *node) {
    return getNodeHeight(node->left) - getNodeHeight(node->right);
}

void AVLTree::balanceHeight(Node *node) {
    int factor = balanceFactor(node);
    if(factor>1){
        rotateRight(node);
    }
    else if(factor<-1){
        rotateLeft(node);
    }
}

Node *AVLTree::rotateRight(Node *node) {
    if(node == root_){
        root_ = node->left;
    }
    Node* new_node = node->left;
    Node *tmp = new_node->right;
    new_node->right = node;
    node->left = tmp;
    return new_node;
}

Node *AVLTree::rotateLeft(Node *node) {
    if(node == root_){
        root_ = node->right;
    }
    Node *new_node = node->right;
    Node *tmp = new_node->left;
    new_node->left = node;
    node->right = tmp;
    return new_node;
}

Node *AVLTree::balanceNode(Node *node) {
    int factor = balanceFactor(node);
    Node *new_node;
    if(factor>1){
        new_node = rotateRight(node);
    }
    else if(factor<-1){
        new_node = rotateLeft(node);
    }
    return new_node;
}

Node *AVLTree::insertNode(Node *node, int value) {
    if(node->value == value){
        return node;
    }
    ++node->height;
    if(node->value > value){
        if(node->left == nullptr){
            node->left = &Node(value);
            return node->left;
        }
        else{
            insertNode(node->left, value);
        }
    }
    else{
        if(node->right == nullptr){
            node->right = &Node(value);
            return node->right;
        }
        else{
            insertNode(node->right, value);
        }
    }
}

Node *AVLTree::findMinNode(Node *node) {
    if(node->left == nullptr){
        return node;
    }
    return findMinNode(node->left);
}

Node *AVLTree::removeMinNode(Node *node) {
    Node *min_node = findMinNode(node);
}

Node *AVLTree::removeNode(Node *node, int value) {
    if(node == nullptr){
        return nullptr;
    }
    if(node->value > value){
        Node *tmp = removeNode(node->left, value);
        if(tmp != nullptr){
            if(node->left!=nullptr && node->right !=nullptr)
                node->height = std::max(node->right->height, node->left->height - 1);
            
        }
        return tmp;
    }
    if(node->value < value){
        Node *tmp = removeNode(node->right, value);
        if(tmp != nullptr){

        }
    }
}

Node *AVLTree::findNode(Node *node, int value) {}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {}