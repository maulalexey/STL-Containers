#ifndef __S21_SET_H__
#define __S21_SET_H__

#include <iostream>
#include <limits>

#include "../Tree/tree.h"

namespace s21 {

template <typename Key>
class set : public Tree<Key, Key> {
  using Tree<Key, Key>::root;
  using Tree<Key, Key>::insertTree;
  using Tree<Key, Key>::printTree;
  using Tree<Key, Key>::copyTree;
  using Tree<Key, Key>::erase;
  using Tree<Key, Key>::deleteTree;
  using Tree<Key, Key>::getSize;
  using typename Tree<Key, Key>::Node;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 public:
  set() : Tree<Key, Key>() {}

  set(std::initializer_list<value_type> const &items) {
    for (const value_type &value : items) {
      insert(value);
      // this->insert(value);
    }
  }

  set(const set &s) : Tree<Key, Key>(s) {}

  set(set &&s) noexcept : Tree<Key, Key>(std::move(s)) {}

  ~set() {}

  set &operator=(set &&s) noexcept {
    if (this != &s) {
      deleteTree(root);
      root = s.root;
      s.root = nullptr;
    }
    return *this;
  }

  // Set Iterators

  class SetIterator {
   public:
    Node *current;
    SetIterator(Node *node) : current(node) {}

    reference operator*() { return current->key; }

    SetIterator &operator++() {
      if (current != nullptr) {
        if (current->right) {
          current = current->right;
          while (current->left) {
            current = current->left;
          }
        } else {
          Node *parent = current->parent;
          while (parent && current == parent->right) {
            current = parent;
            parent = parent->parent;
          }
          current = parent;
        }
      }
      return *this;
    }

    SetIterator operator++(int) {
      SetIterator tmp = *this;
      ++(*this);
      // operator++();
      return tmp;
    }

    SetIterator &operator--() {
      if (current != nullptr) {
        if (current->left) {
          current = current->left;
          while (current->right) {
            current = current->right;
          }
        } else {
          Node *parent = current->parent;
          while (parent && current == parent->left) {
            current = parent;
            parent = parent->parent;
          }
          current = parent;
        }
      }
      return *this;
    }

    SetIterator operator--(int) {
      SetIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const SetIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const SetIterator &other) const {
      return current != other.current;
    }
  };

  using iterator = SetIterator;

  iterator begin() {  // возвращает указатель на первый эл-нт контейнера, в
                      // контексе set им является наименьший элемент
    Node *current = root;
    while (current && current->left) {
      current =
          current->left;  // наименьший эл-нт находится в самом низу левой ветви
    }
    return iterator(current);
  }

  iterator end() { return iterator(nullptr); }

  class SetConstIterator : public SetIterator {
   public:
    SetConstIterator(Node *node) : SetIterator(node) {}

    const_reference operator*() const { return this->current->key; }
  };

  using const_iterator = SetConstIterator;

  // Set Capacity

  bool empty() {
    if (root == nullptr) {
      return true;
    } else {
      return false;
    }
  }

  size_type size() {
    int count = 0;
    return getSize(root, count);
  }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Key);
  }

  // Set Modifiers

  void clear() {
    deleteTree(root);
    root = nullptr;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    Node *pt = new Node(value);
    // root = BSTInsert(root, pt);
    if (root == nullptr) {
      root = pt;
      return {iterator(pt), true};
    }
    Node *insertedNode = insertTree(root, pt);

    if (insertedNode == pt) {
      return {iterator(pt), true};
    } else {
      return {iterator(insertedNode), false};
    }
  }

  void erase(iterator pos) {
    if (pos.current != nullptr) {
      root = erase(root, pos.current->key);
    }
  }

  void swap(set &other) {
    Node *tmp = this->root;
    this->root = copyTree(other.root);
    other.root = copyTree(tmp);
    // std::swap(this->root, other.root);
  }

  void merge(set &other) {
    for (auto iter{other.begin()}; iter != other.end(); ++iter) {
      Node *pt = new Node(*iter);
      root = insertTree(root, pt);
    }
  }

  // Set Lookup

  iterator find(const Key &key) {
    Node *current = root;
    while (current != nullptr) {
      if (current->key == key) {
        return iterator(current);
      }
      if (key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return end();
  }

  bool contains(const Key &key) {
    Node *current = root;
    while (current != nullptr) {
      if (current->key == key) {
        return true;
      }
      if (key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return false;
  }

  void print() { printTree(root); }
};
}  // namespace s21

#endif