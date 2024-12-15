#include <algorithm>

struct Node {
  Node(int key, Node *parent);

  int key;
  Node *left;
  Node *right;
  Node *parent;
};

class SplayTree {
public:
  SplayTree();

  ~SplayTree();

  void insert(int);

  Node *find(int) const;

  int splay(Node *);

  int getHeight() const;

  Node *root;

  void clear(Node *node);

  void rotateLeft(Node *node);

  void rotateRight(Node *node);

  int getHeight(Node *node) const;
};

Node::Node(int key, Node *parent)
    : key(key), left(nullptr), right(nullptr), parent(parent) {}

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree() { clear(root); }

void SplayTree::insert(int key) {
  Node *current = root;
  Node *parent = nullptr;

  while (current) {
    parent = current;
    if (key < current->key) {
      current = current->left;
    } else if (key > current->key) {
      current = current->right;
    } else {
      return;
    }
  }

  current = new Node(key, nullptr);
  current->parent = parent;

  if (!parent) {
    root = current;
  } else if (key < parent->key) {
    parent->left = current;
  } else {
    parent->right = current;
  }
}

Node *SplayTree::find(int key) const {
  Node *temp = root;

  while (temp != nullptr) {
    if (key == temp->key) {
      return temp;
    } else if (key < temp->key) {
      temp = temp->left;
    } else {
      temp = temp->right;
    }
  }

  return nullptr;
}

int SplayTree::splay(Node *node) {
  int rots = 0;

  while (node != root) {
    if (node->parent == root) {
      if (node->parent->left == node) {
        rotateRight(node->parent);
      } else {
        rotateLeft(node->parent);
      }
      rots++;
    } else {
      if (node->parent->left == node &&
          node->parent->parent->left == node->parent) {
        rotateRight(node->parent->parent);
        rotateRight(node->parent);
        ++rots;
      } else if (node->parent->right == node &&
                 node->parent->parent->right == node->parent) {
        rotateLeft(node->parent->parent);
        rotateLeft(node->parent);
        ++rots;
      } else if (node->parent->left == node &&
                 node->parent->parent->right == node->parent) {
        rotateRight(node->parent);
        rotateLeft(node->parent);
      } else {
        rotateLeft(node->parent);
        rotateRight(node->parent);
      }

      rots++;
    }
  }
  return rots;
}

int SplayTree::getHeight() const { return getHeight(root); }

void SplayTree::clear(Node *node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

void SplayTree::rotateLeft(Node *node) {
  Node *right = node->right;
  if (right) {
    node->right = right->left;
    if (right->left) {
      right->left->parent = node;
    }
    right->parent = node->parent;
    if (!node->parent) {
      root = right;
    } else if (node == node->parent->left) {
      node->parent->left = right;
    } else {
      node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
  }
}

void SplayTree::rotateRight(Node *node) {
  Node *left = node->left;
  if (left) {
    node->left = left->right;
    if (left->right) {
      left->right->parent = node;
    }
    left->parent = node->parent;
    if (!node->parent) {
      root = left;
    } else if (node == node->parent->right) {
      node->parent->right = left;
    } else {
      node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
  }
}

int SplayTree::getHeight(Node *node) const {
  if (node == nullptr) {
    return -1;
  }
  return 1 + std::max(getHeight(node->left), getHeight(node->right));
}