//
//  main.cpp
//  treeiterator
//
//  Created by Roman N. on 25.11.2024. Edited by
//

#include <iostream>
using std::cin;
using std::cout;

template <class T> struct Node {
  T data;
  Node *right;
  Node *left;
  Node *parent;

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
          p->left = p->left->left;
          p->left = p;
          break;
        } else {
          p = p->left;
        }
      } else {
        if (p->right == value) {
          p->right = p->right->right;
          p->right = p;
          break;
        } else {
          p = p->right;
        }
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
        if ((ptr_->parent)->data < ptr_->data) {
          ptr_ = ptr_->parent;
        } else {
          ptr_ = nullptr;
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
        if ((ptr_->parent)->data > ptr_->data) {
          ptr_ = ptr_->parent;
        } else {
          ptr_ = nullptr;
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

int main() {

  // input data
  int n;
  std::cin >> n;
  int root;
  std::cin >> root;
  Tree<int> tree{root};
  for (size_t i = 0; i < n - 1; ++i) {
    int tmp;
    std::cin >> tmp;
    tree.insert(tmp);
  }

  // testing
  std::cout << "tree successor:\n";
  for (Node<int> node : tree) {
    std::cout << node << ' ';
  }
  std::cout << "\ntree predecessor:\n";
  for (auto iter = tree.rbegin(); iter != nullptr; --iter) {
    std::cout << (*iter).data << ' ';
  }
}
