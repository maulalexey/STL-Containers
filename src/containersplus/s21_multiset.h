#ifndef __S21_MULTISET_H__
#define __S21_MULTISET_H__

#include <iostream>
#include <limits>
#include <stack>

#include "../Tree/tree.h"

namespace s21 {

template <typename Key>
class multiset : public Tree<Key, Key> {
  using Tree<Key, Key>::root;
  using Tree<Key, Key>::insertTree;
  using Tree<Key, Key>::printTree;
  using Tree<Key, Key>::copyTree;
  using Tree<Key, Key>::erase;
  using Tree<Key, Key>::deleteTree;
  using Tree<Key, Key>::getSize;
  using Tree<Key, Key>::insertWithDuplicates; 
  using typename Tree<Key, Key>::Node;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 public:
  multiset() : Tree<Key, Key>() {}

  multiset(std::initializer_list<value_type> const& items) {
    for (const value_type& value : items) {
      insert(value);
    }
  }

  multiset(const multiset& s) : Tree<Key, Key>(s) {}

  multiset(multiset&& s) noexcept : Tree<Key, Key>(std::move(s)) {}

  ~multiset() {}

  multiset& operator=(multiset&& s) noexcept {
    if (this != &s) {
      deleteTree(root);
      root = s.root;
      s.root = nullptr;
    }
    return *this;
  }

  class MultisetIterator {
   public:
    Node* current;
    MultisetIterator(Node* node) : current(node) {}

    reference operator*() { return current->key; }

    MultisetIterator& operator++() {
      if (current != nullptr) {
        if (current->right) {
          current = current->right;
          while (current->left) {
            current = current->left;
          }
        } else {
          Node* parent = current->parent;
          while (parent && current == parent->right) {
            current = parent;
            parent = parent->parent;
          }
          current = parent;
        }
      }
      return *this;
    }

    MultisetIterator operator++(int) {
      MultisetIterator tmp = *this;
      ++(*this);
      // operator++();
      return tmp;
    }

    MultisetIterator& operator--() {
      if (current != nullptr) {
        if (current->left) {
          current = current->left;
          while (current->right) {
            current = current->right;
          }
        } else {
          Node* parent = current->parent;
          while (parent && current == parent->left) {
            current = parent;
            parent = parent->parent;
          }
          current = parent;
        }
      }
      return *this;
    }

    MultisetIterator operator--(int) {
      MultisetIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const MultisetIterator& other) const {
      return current == other.current;
    }

    bool operator!=(const MultisetIterator& other) const {
      return current != other.current;
    }
  };

  using iterator = MultisetIterator;

  iterator begin() {
    Node* current = root;
    while (current && current->left) {
      current = current->left;
    }
    return iterator(current);
  }

  iterator end() { return iterator(nullptr); }

  class MultisetConstIterator : public MultisetIterator {
   public:
    MultisetConstIterator(Node* node) : MultisetIterator(node) {}

    const_reference operator*() const { return this->current->key; }
  };

  using const_iterator = MultisetConstIterator;

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

  void clear() {
    deleteTree(root);
    root = nullptr;
  }

  iterator insert(const value_type& value) {
    Node* pt = new Node(value);

    if (root == nullptr) {
      root = pt;
      return iterator(pt);
    }
    Node* insertedNode = insertWithDuplicates(root, pt);

    if (insertedNode == pt) {
      return iterator(pt);
    } else {
      return iterator(insertedNode);
    }
  }

  void erase(iterator pos) {
    if (pos.current != nullptr) {
      root = erase(root, pos.current->key);
    }
  }

  void swap(multiset& other) {
    Node* tmp = this->root;
    this->root = copyTree(other.root);
    other.root = copyTree(tmp);
  }

  void merge(multiset& other) {
    for (auto iter{other.begin()}; iter != other.end(); ++iter) {
      Node* pt = new Node(*iter);
      root = insertTree(root, pt);
    }
  }

  // Multiset Lookup

  size_type count(const Key& key) { return countElement(root, key); }

  size_type countElement(Node* node, const Key& key) {
    size_type count = 0;
    if (node == nullptr) {
      return 0;
    }
    if (node->key == key) {
      count = 1;
    } else {
      count = 0;
    }
    count += countElement(node->left, key);
    count += countElement(node->right, key);
    return count;
  }

  iterator find(const Key& key) {
    Node* current = root;
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

  bool contains(const Key& key) {
    Node* current = root;
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

  std::pair<iterator, iterator> equal_range(const Key& key) {
    iterator first_iter = lower_bound(key);
    iterator second_iter = upper_bound(key);
    return std::make_pair(first_iter, second_iter);
  }

  iterator lower_bound(const Key& key) {
    // возвращает итератор на первый элемент, который больше или равен (не
    // меньше)заданному ключу
    Node* current = root;
    Node* result = nullptr;

    while (current != nullptr) {
      if (current->key >= key) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    if (result != nullptr) {
      return iterator(result);
    } else {
      return end();
    }
  }

  iterator upper_bound(const Key& key) {
    Node* current = root;
    Node* result = nullptr;

    while (current != nullptr) {
      if (current->key > key) {
        result = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }

    if (result != nullptr) {
      return iterator(result);
    } else {
      return end();
    }
  }

  void print() { printTree(root); }
};
}  // namespace s21

#endif