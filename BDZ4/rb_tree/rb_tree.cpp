#include "rbtree.h"
#include <algorithm>

static int sizeRB(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  return 1 + sizeRB(node->left) + sizeRB(node->right);
}

Node *findRB(Node *node, int key) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->key < key) {
    return findRB(node->right, key);
  } else if (node->key > key) {
    return findRB(node->left, key);
  }
  return node;
}

static void deleteRB(Node *node) {
  if (node == nullptr) {
    return;
  }
  deleteRB(node->left);
  deleteRB(node->right);
  delete node;
}

static void rotateRight(Node *&node, Node *&root) {
  Node *child = node->left;
  node->left = child->right;
  if (node->left != nullptr) {
    node->left->parent = node;
  }
  child->parent = node->parent;

  if (node->parent == nullptr) {
    root = child;
  } else if (node == node->parent->left) {
    node->parent->left = child;
  } else {
    node->parent->right = child;
  }
  child->right = node;
  node->parent = child;
}

static void rotateLeft(Node *&node, Node *&root) {
  Node *child = node->right;
  node->right = child->left;
  if (node->right != nullptr) {
    node->right->parent = node;
  }
  child->parent = node->parent;
  if (node->parent == nullptr) {
    root = child;
  } else if (node == node->parent->left) {
    node->parent->left = child;
  } else {
    node->parent->right = child;
  }

  child->left = node;
  node->parent = child;
}

Node::Node(int key)
    : key(key), height(1), size(1), left(nullptr), right(nullptr),
      parent(nullptr), color(Color::RED) {}

RBTree::RBTree() : root(nullptr) {}

RBTree::RBTree(std::initializer_list<int> list) : root(nullptr) {
  for (int key : list) {
    insert(key);
  }
}

RBTree::~RBTree() { deleteRB(root); }

void RBTree::insert(int key) {
  Node *node = new Node(key);
  Node *parent = nullptr;
  Node *current = root;

  while (current != nullptr) {
    parent = current;
    if (node->key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  node->parent = parent;
  if (parent == nullptr) {
    root = node;
  } else if (node->key < parent->key) {
    parent->left = node;
  } else if (node->key > parent->key) {
    parent->right = node;
  } else {
    return;
  }

  node->color = Color::RED;
  while (node != root && node->color == Color::RED &&
         node->parent->color == Color::RED) {
    Node *parent = node->parent;
    Node *grandparent = parent->parent;

    if (parent == grandparent->left) {
      Node *uncle = grandparent->right;

      if (uncle != nullptr && uncle->color == Color::RED) {
        grandparent->color = Color::RED;
        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node = grandparent;
      } else {
        if (node == parent->right) {
          rotateLeft(parent, root);
          node = parent;
          parent = node->parent;
        }

        rotateRight(grandparent, root);
        std::swap(parent->color, grandparent->color);
        node = parent;
      }
    } else {
      Node *uncle = grandparent->left;

      if (uncle != nullptr && uncle->color == Color::RED) {
        grandparent->color = Color::RED;
        parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        node = grandparent;
      } else {
        if (node == parent->left) {
          rotateRight(parent, root);
          node = parent;
          parent = node->parent;
        }

        rotateLeft(grandparent, root);
        std::swap(parent->color, grandparent->color);
        node = parent;
      }
    }
  }

  root->color = Color::BLACK;
}

int *RBTree::find(int key) {
  Node *temp = findRB(root, key);
  if (temp) {
    return &(temp->key);
  } else {
    return nullptr;
  }
}

int RBTree::size() const { return sizeRB(root); }

int *RBTree::lowerBound(int key) {
  Node *current = root;
  Node *result = nullptr;

  while (current != nullptr) {
    if (current->key >= key) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return result ? &result->key : nullptr;
}

bool RBTree::empty() const { return root == nullptr; }