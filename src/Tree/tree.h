#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include <limits>

namespace s21 {
    template <typename Key, typename Value>
class Tree {
protected:
    struct Node {
        Key key;
        Value value;
        Node* parent;
        Node* left;
        Node* right;
        int height;

        Node(const std::pair<const Key, Value>& pair)
        : key(pair.first), value(pair.second), parent(nullptr), left(nullptr), right(nullptr), height(0) {}

        Node(const Key& key_value)
        : key(key_value), value(key_value), parent(nullptr), left(nullptr), right(nullptr), height(0) {}
    };
    Node* root;

public:
    Tree() : root(nullptr) {}

    Tree(const Tree &other) : root(nullptr) {
        root = copyTree(other.root);
    }

    Tree(Tree &&other) noexcept {
        this -> root = other.root;
        other.root = nullptr;
    }

    ~Tree() {
        deleteTree(root);
        root = nullptr;
    }

    // Balance Tree
    int getHeight(Node* node) {
        return node == nullptr ? -1 : node->height;
    }

    void updateHeight(Node* node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(Node* node) {
        return (node == nullptr) ? 0 : getHeight(node->right) - getHeight(node->left); 
    }

    void swap(Node* a, Node* b) {
        Key a_key = a->key;
        a->key = b->key;
        b->key = a_key;
        Value a_value = a->value;
        a->value = b->value;
        b->value = a_value;
    }

    void rightRotate(Node* node) {
        swap(node, node->left);
        Node* buffer = node->right;
        node->right = node->left;
        node->left = node->right->left;
        node->right->left = node->right->right;
        node->right->right = buffer;
        updateHeight(node->right);
        updateHeight(node);
    }

    void leftRotate(Node* node) {
        swap(node, node->right);
        Node* buffer = node->left;
        node->left = node->right;
        node->right = node->left->right;
        node->left->right = node->left->left;
        node->left->left = buffer;
        updateHeight(node->left);
        updateHeight(node);
    }

    void balance(Node* node) {
        int balance = getBalance(node);
        if (balance == -2) {
            if (getBalance(node->left) == 1) leftRotate(node->left);
            rightRotate(node);
        } else if (balance == 2) {
            if (getBalance(node->right) == -1) rightRotate(node->right);
            leftRotate(node);
        }
    }

    Node* insertTree(Node* root, Node* pt) {
        if (root == nullptr) {
            return pt;
        }
        if (pt->key == root->key) {
            return root;
        }
        if (pt->key < root->key) {
            root->left = insertTree(root->left, pt);
            root->left->parent = root;
        } else {
            root->right = insertTree(root->right, pt);
            root->right->parent = root;
        }
        updateHeight(root);
        balance(root);
        return root;
    }

    Node* insertWithDuplicates(Node* root, Node* pt) {
        if (root == nullptr) {
            return pt;
        }

        if (pt->key < root->key) {
            root->left = insertWithDuplicates(root->left, pt);
            root->left->parent = root;
        } else {
            root->right = insertWithDuplicates(root->right, pt);
            root->right->parent = root;
        }
        updateHeight(root);
        balance(root);
        return root;
    }

    Node* assign(Node* node, Node* pt) {
        if (node == nullptr) {
            return pt;
        }
        if (pt->key == root->key) {
            return pt;
        }
        if (pt->key < root->key) {
            root->left = insertTree(root->left, pt);
            root->left->parent = root;
        } else {
            root->right = insertTree(root->right, pt);
            root->right->parent = root;
        }
        updateHeight(root);
        balance(root);
        return root;
    }

    void printTree(Node* node) {
        if (node == nullptr) {
            return ;
        }
        printTree(node -> left);
        // std::cout << node->key << std::endl;
        std::cout << node->value << std::endl;
        printTree(node -> right);
    }

    void assign(Node* node, const Value& obj) {
        if (node != nullptr) {
            node->value = obj;
        }
    }

    Node* copyTree(Node* node) {
        if (!node) {
            return nullptr;
        }

        Node* newNode;
        if constexpr (std::is_same_v<Value, void>) {
            newNode = new Node(node->key);
        } else {
            newNode = new Node(std::make_pair(node->key, node->value));
        }

        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        if (newNode->left) {
            newNode->left->parent = newNode;
        }
        if (newNode->right) {
            newNode->right->parent = newNode;
        }
        return newNode;
    }

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node -> left);
            deleteTree(node -> right);

            delete node;
        }
    }

    Node* findInTree(Node* root, const Key& key) {
        if (root == nullptr || root->key == key) {
            return root;
        }

        if (key < root->key) {
            return findInTree(root->left, key);
        } else {
            return findInTree(root->right, key);
        }
    }

    int getSize(Node* node, int& count) {
        if (node == nullptr) {
            return 0;
        }

        count += 1;
        getSize(node -> left, count);
        getSize(node -> right, count);
  
        return count;
        // return 1 + getSize(node->left) + getSize(node->right);
    }

    Node* getMin(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left; 
        }
        return current;
    }

    Node* erase(Node* root, const Key& key) {
        if (root == nullptr) {
            return root; 
        }

        if (key < root->key) {
            root->left = erase(root->left, key);
        } else if (key > root->key) {
            root->right = erase(root->right, key);
        } else {

            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root; 
                return temp; 
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = getMin(root->right);
            root->key = temp->key; 
            root->right = erase(root->right, temp->key); 
        }
        updateHeight(root);
        balance(root);
        return root;
    }
};
}

#endif