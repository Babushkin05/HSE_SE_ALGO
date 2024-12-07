//
//  main.cpp
//  treeiterator
//
//  Created by Roman N. on 25.11.2024. Edited by Vovs Babushkin
//

#include <iostream>
using std::cin;
using std::cout;

template <class T> struct Node {
  T data;
  Node *right;
  Node *left;
  Node *parent;
  size_t height = 0;

  Node(T val = {}) {
    data = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

template <class T> std::ostream &operator<<(std::ostream &sout, Node<T> &elem) {
  sout << elem.data;
  return sout;
}

template <class T> class Tree {
public:
  Tree(T value) { root = new Node<T>(value); }

  Node<T> *insert(T value) {
    Node<T> *tmp = new Node<T>(value);
    Node<T> *p = root;
    while (tmp->parent == nullptr) {
      if (p->data > tmp->data) {
        if (p->left == nullptr) {
          p->left = tmp;
          tmp->parent = p;
        } else {
          p = p->left;
        }
      } else {
        if (p->right == nullptr) {
          p->right = tmp;
          tmp->parent = p;
        } else {
          p = p->right;
        }
      }
    }
    return tmp;
  }

  Node<T> *erase(T value) {
    Node<T> *p = root;
    while (true) {
      if (p->data > value) {
        if (p->left->data == value) {
          Node<T> *tmp = p->left;
          p->left = tmp->left;
          if (p->left != nullptr)
            p->left->parent = p;
          return tmp;
        } else {
          p = p->left;
        }
      } else if (p->data < value) {
        if (p->right->data == value) {
          Node<T> *tmp = p->left;
          p->right = tmp->right;
          if (p->right != nullptr)
            p->right->parent = p;
          return tmp;
        } else {
          p = p->right;
        }
      }
    }
  }

  Node<T> *find(T value) {
    Node<T> *p = root;
    while (true) {
      if (p->data > value) {
        if (p->left == nullptr) {
          return nullptr;
        } else {
          p = p->left;
        }
      } else if (p->data < value) {
        if (p->right == nullptr) {
          return nullptr;
        } else {
          p = p->right;
        }
      } else {
        return p;
      }
    }
  }

  struct Iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Node<T>;
    using pointer = Node<T> *; // or also value_type*
    using reference = Node<T> &;

    Iterator(pointer ptr) : ptr_(ptr) {}

    reference operator*() { return *ptr_; }

    pointer operator->() { return ptr_; }

    Iterator &operator--() {
      if (ptr_->left != nullptr) {
        ptr_ = ptr_->left;
        while (ptr_->right != nullptr) {
          ptr_ = ptr_->right;
        }
      } else if (ptr_->parent == nullptr) {
        ptr_ = nullptr;
      } else if ((ptr_->parent)->data < ptr_->data) {
        ptr_ = ptr_->parent;
      } else {
        ptr_ = ptr_->parent;
        if (ptr_->parent == nullptr) {
          ptr_ = nullptr;
          return *this;
        }
        while (ptr_->data < (ptr_ = ptr_->parent)->data) {
          if (ptr_->parent == nullptr) {
            ptr_ = nullptr;
            break;
          }
        }
      }
      return *this;
    }

    Iterator &operator++() {
      if (ptr_->right != nullptr) {
        ptr_ = ptr_->right;
        while (ptr_->left != nullptr) {
          ptr_ = ptr_->left;
        }
      } else if (ptr_->parent == nullptr) {
        ptr_ = nullptr;
      } else if ((ptr_->parent)->data > ptr_->data) {
        ptr_ = ptr_->parent;
      } else {
        ptr_ = ptr_->parent;
        if (ptr_->parent == nullptr) {
          ptr_ = nullptr;
          return *this;
        }
        while (ptr_->data > (ptr_ = ptr_->parent)->data) {
          if (ptr_->parent == nullptr) {
            ptr_ = nullptr;
            break;
          }
        }
      }
      return *this;
    }

    // Необходимые для пользования итераторами методы
    friend bool operator==(const Iterator &it1, const Iterator &it2) {
      return (it1.ptr_ == it2.ptr_);
    }

    friend bool operator!=(const Iterator &it1, const Iterator &it2) {
      return (it1.ptr_ != it2.ptr_);
    }

  private:
    pointer ptr_;
  };

  // Минимум, начало дерева
  Iterator begin() {
    Node<T> *it = root;
    while (it->left != nullptr) {
      it = it->left;
    }
    return Iterator(it);
  }

  // Максимум, конец дерева
  Iterator end() { return nullptr; }

  Iterator rbegin() {
    Node<T> *it = root;
    while (it->right != nullptr) {
      it = it->right;
    }
    return Iterator(it);
  }

  Iterator rend() { return nullptr; }

private:
  Node<T> *root;
};

template <class T> bool avl_checker(Node<T> *node) {
  if (node == nullptr) {
    return true;
  }
  bool f = avl_checker(node->left) & avl_checker(node->right);
  int l = 0;
  int r = 0;
  if (node->left != nullptr) {
    l = node->left->height + 1;
  }
  if (node->right != nullptr) {
    r = node->right->height + 1;
  }
  node->height = std::max(l, r);
  return f && std::abs(l - r) < 2;
}

int main() {
  int root;
  std::cin >> root;
  if (root == 0) {
    std::cout << "YES";
    return 0;
  }
  Tree<int> tree{root};
  Node<int> *rootnode = tree.find(root);
  int a;
  while (true) {
    std::cin >> a;
    if (a == 0) {
      break;
    }
    tree.insert(a);
  }
  bool f = avl_checker(rootnode);
  if (f) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
