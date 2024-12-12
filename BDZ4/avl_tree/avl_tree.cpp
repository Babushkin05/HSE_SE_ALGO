#include "avl_tree.h"
#include <algorithm>
#include <functional>
#include <math.h>

Node::Node(int value)
    : value(value), height(1), left(nullptr), right(nullptr) {}

Node::~Node() {}

AVLTree::AVLTree() : root_(nullptr), size_(0) {}

AVLTree::AVLTree(int value) : root_(new Node(value)), size_(1) {}

int AVLTree::getHeight() { return getNodeHeight(root_); }

void AVLTree::insert(int value) {
  if (find(value) != nullptr) {
    return;
  }
  root_ = insertNode(root_, value);
  size_++;
}

void AVLTree::erase(int value) {
  if (find(value) == nullptr) {
    return;
  }
  root_ = removeNode(root_, value);
  size_--;
}

int *AVLTree::find(int value) {
  Node *node = findNode(root_, value);

  if (node == nullptr) {
    return nullptr;
  }
  return &node->value;
}

int *AVLTree::traversal() {
  if (empty()) {
    return nullptr;
  }

  int *array = new int[size_];
  int index = 0;

  traversalInternal(root_, array, &index);
  return array;
}

int *AVLTree::lowerBound(int value) {
  Node *node = lowerBoundInternal(root_, value);

  return node ? &node->value : nullptr;
}

bool AVLTree::empty() { return size_ == 0; }

Node *AVLTree::getRoot() { return root_; }

int AVLTree::getSize() { return size_; }

AVLTree::~AVLTree() {
  while (root_) {
    root_ = removeNode(root_, root_->value);
  }
  size_ = 0;
}

int AVLTree::getNodeHeight(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

int AVLTree::balanceFactor(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return getNodeHeight(node->left) - getNodeHeight(node->right);
}

void AVLTree::balanceHeight(Node *node) {
  if (node != nullptr) {
    node->height =
        1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
  }
}

Node *AVLTree::rotateRight(Node *node) {
  Node *left = node->left;
  Node *rightOfLeft = left->right;

  left->right = node;
  node->left = rightOfLeft;

  balanceHeight(node);
  balanceHeight(left);

  return left;
}

Node *AVLTree::rotateLeft(Node *node) {
  Node *right = node->right;
  Node *leftOfRight = right->left;

  right->left = node;
  node->right = leftOfRight;

  balanceHeight(node);
  balanceHeight(right);

  return right;
}

Node *AVLTree::balanceNode(Node *node) {
  balanceHeight(node);
  int balance = balanceFactor(node);
  if (balance > 1 && balanceFactor(node->left) >= 0) {
    return rotateRight(node);
  }
  if (balance > 1 && balanceFactor(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && balanceFactor(node->right) <= 0) {
    return rotateLeft(node);
  }
  if (balance < -1 && balanceFactor(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

Node *AVLTree::insertNode(Node *node, int value) {
  if (node == nullptr) {
    return new Node(value);
  }
  if (value < node->value) {
    node->left = insertNode(node->left, value);
  } else if (value > node->value) {
    node->right = insertNode(node->right, value);
  } else {
    return node;
  }
  return balanceNode(node);
}

Node *AVLTree::findMinNode(Node *node) {
  return node->left ? findMinNode(node->left) : node;
}

Node *AVLTree::removeMinNode(Node *node) {
  if (node->left != nullptr) {
    return node->right;
  }
  node->left = removeMinNode(node->left);
  return balanceNode(node);
}

Node *AVLTree::removeNode(Node *node, int value) {
  if (node == nullptr) {
    return nullptr;
  }
  if (value < node->value) {
    node->left = removeNode(node->left, value);
  } else if (value > node->value) {
    node->right = removeNode(node->right, value);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      Node *temp = node->left ? node->left : node->right;
      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
      }
      delete temp;
    } else {
      Node *temp = findMinNode(node->right);
      node->value = temp->value;
      node->right = removeNode(node->right, temp->value);
    }
  }
  if (node == nullptr) {
    return nullptr;
  }
  node->height =
      1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
  int balance = balanceFactor(node);
  if (balance > 1 && balanceFactor(node->left) >= 0) {
    return rotateRight(node);
  }
  if (balance > 1 && balanceFactor(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && balanceFactor(node->right) <= 0) {
    return rotateLeft(node);
  }
  if (balance < -1 && balanceFactor(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  return node;
}

Node *AVLTree::findNode(Node *node, int value) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->value == value) {
    return node;
  }
  if (node->value < value) {
    return findNode(node->right, value);
  }
  return findNode(node->left, value);
}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {
  if (node == nullptr) {
    return;
  }
  traversalInternal(node->left, array, index);
  array[(*index)++] = node->value;
  traversalInternal(node->right, array, index);
}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {
  if (!current) {
    return nullptr;
  }
  if (current->value == value) {
    return current;
  }
  if (current->value > value) {
    Node *left = lowerBoundInternal(current->left, value);

    return left ? left : current;
  }
  return lowerBoundInternal(current->right, value);
}