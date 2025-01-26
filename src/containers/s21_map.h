#ifndef __S21_MAP_H__
#define __S21_MAP_H__

#include <iostream>
#include <limits>

#include "../Tree/tree.h"

namespace s21 {

template <typename Key, typename T>
class map : public Tree<Key, T> {
 public:
  using Tree<Key, T>::root;
  using typename Tree<Key, T>::Node;
  using Tree<Key, T>::insertTree;
  using Tree<Key, T>::printTree;
  using Tree<Key, T>::findInTree;
  using Tree<Key, T>::getSize;
  using Tree<Key, T>::deleteTree;
  using Tree<Key, T>::erase;
  using Tree<Key, T>::copyTree;
  using Tree<Key, T>::assign;

  // Map Member type
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using size_type = size_t;
  using const_reference = const value_type &;

  // Map Member functions
  map() : Tree<Key, T>() {}

  map(std::initializer_list<value_type> const &items) {
    for (const value_type &value : items) {
      insert(value);
      // this->insert(value);
    }
  }

  map(const map &other) : Tree<Key, T>(other){};

  map(map &&other) noexcept : Tree<Key, T>(std::move(other)){};

  ~map() {}

  map &operator=(map &&m) {
    if (this != &m) {
      // this->clear();
      deleteTree(root);
      root = m.root;
      m.root = nullptr;
    }
    return *this;
  }

  // Map Element access

  T &at(const Key &key) {
    Node *current = root;

    while (current != nullptr) {
      if (key == current->key) {
        return current->value;
      }
      if (key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    throw std::out_of_range("Not found key");
  }

  T &operator[](const Key &key) {
    Node *node = findInTree(root, key);
    if (node == nullptr) {
      Node *newNode = new Node(std::make_pair(key, T()));
      root = insertTree(root, newNode);
      return newNode->value;
    } else {
      return node->value;
    }
  }

  // Map Iterators

  class MapIterator {
   public:
    Node *current;
    MapIterator(Node *node) : current(node) {}

    std::pair<const Key, T> operator*() {
      return {current->key, current->value};
    }

    // reference operator*() {
    //     return *reinterpret_cast<value_type*>(&current->key);
    // }

    std::pair<const Key, T> &operator->() {
      return {current->key, current->value};
    }

    // reference operator->() {
    //     return *reinterpret_cast<value_type*>(&current->key);
    // }

    MapIterator &operator++() {
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

    MapIterator operator++(int) {
      MapIterator tmp = *this;
      ++(*this);
      // operator++();
      return tmp;
    }

    MapIterator &operator--() {
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

    MapIterator operator--(int) {
      MapIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const MapIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const MapIterator &other) const {
      return current != other.current;
    }
  };

  using iterator = MapIterator;

  iterator begin() {
    Node *current = root;
    while (current && current->left) {
      current = current->left;
    }
    return iterator(current);
  }

  iterator end() { return iterator(nullptr); }

  class MapConstIterator : public MapIterator {
   public:
    MapConstIterator(Node *node) : MapIterator(node) {}

    const std::pair<const Key, T> operator*() {
      return {this->current->key, this->current->value};
    }
  };

  using const_iterator = MapConstIterator;

  // Map Capacity

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
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  // Map Modifiers

  void clear() {
    deleteTree(root);
    root = nullptr;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    Node *pt = new Node(value);

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

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    auto value = std::make_pair(key, obj);
    Node *pt = new Node(value);

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

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto value = std::make_pair(key, obj);
    Node *pt = new Node(value);

    if (root == nullptr) {
      root = pt;
      return {iterator(pt), true};
    }

    Node *exNode = findInTree(root, key);
    if (exNode) {
      // exNode->value = obj;
      assign(root, obj);
      return {iterator(exNode), false};
    }

    Node *insertedNode = insertTree(root, pt);
    return {iterator(pt), true};
  }

  void erase(iterator pos) {
    if (pos.current != nullptr) {
      root = erase(root, pos.current->key);
    }
  }

  void swap(map &other) {
    Node *tmp = this->root;
    this->root = copyTree(other.root);
    other.root = copyTree(tmp);
  }

  void merge(map &other) {
    for (auto iter{other.begin()}; iter != other.end(); ++iter) {
      Node *pt = new Node(*iter);
      root = insertTree(root, pt);
    }
  }

  // Map Lookup

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