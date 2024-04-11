#pragma once

#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

// A binary search tree with specialized methods for initialization,
// traversal, and visualization.
template <typename K, typename V>
class BinarySearchTree {
private:

    // A node in the binary tree.
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
    };

    Node* root;

    // Creates a new node with the given key and value.
    Node* makeNode(const K& key, const V& value) {
        Node* node = new Node;
        node->key = key;
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    // Frees all memory associated with the given node and its children.
    void deleteTree(Node *node) {
        if (!node) {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }

    // Performs an "upsert": If the given key already exists, its value
    // is replaced with the given one, otherwise a new key/value is added.
    void put(const K& key, const V& value, Node *node) {
        // TODO
    }

    // Searches for the key starting at the given node.
    // The key must exist, otherwise an exception is thrown.
    const V& get(const K& key, Node *node) const {
        if (!node) {
            throw std::runtime_error("Key not found");
        }

        if (key < node->key) {
            return get(key, node->left);
        } else if (key > node->key) {
            return get(key, node->right);
        } else {
            return node->value;
        }
    }

    // Returns true if the given key exists in the subtree starting
    // at the given node.
    bool exists(const K& key, Node* node) const {
        if (!node) {
            return false;
        }

        if (key < node->key) {
            return exists(key, node->left);
        } else if (key > node->key) {
            return exists(key, node->right);
        } else {
            return true;
        }
    }

    // Performs an inorder traversal starting at the given node. Invokes
    // the given lambda at each node.
    void traverseInorder(Node* node, std::function<void(const K&, const V&)> visit) {
        if (!node) {
            return;
        }

        traverseInorder(node->left, visit);
        visit(node->key, node->value);
        traverseInorder(node->right, visit);
    }

    // Performs a preorder traversal of the subtree starting at the given node.
    // Invokes the appropriate lambdas before and after each descent. Halts the
    // traversal if the shouldStop lambda returns true.
    bool traversePreorder(Node* node,
                          std::function<bool(const K& key, const V& value)> shouldStop,
                          std::function<void(void)> beginLeft,
                          std::function<void(void)> endLeft,
                          std::function<void(void)> beginRight,
                          std::function<void(void)> endRight) const {
        if (!node) {
            return false;
        }

        if (shouldStop(node->key, node->value)) {
            return true;
        }

        beginLeft();
        if (traversePreorder(node->left, shouldStop, beginLeft, endLeft, beginRight, endRight)) {
            return true;
        }
        endLeft();

        beginRight();
        if (traversePreorder(node->right, shouldStop, beginLeft, endLeft, beginRight, endRight)) {
            return true;
        }
        endRight();

        return false;
    }

    // Writes the given subtree in DOT format to the output stream. The id is incremented to give
    // each node a unique ID.
    void writeDOT(Node* node, std::ostream& out, int& id) const {
        int parentID = id;
        out << parentID << "[label=\"" << node->key << ": " << node->value << "\"]" << std::endl;

        if (node->left) {
            id++;
            out << parentID << " -> " << id << std::endl;
            writeDOT(node->left, out, id);
        }

        if (node->right) {
            id++;
            out << parentID << " -> " << id << std::endl;
            writeDOT(node->right, out, id);
        }
    }

    // Creates a copy of the subtree starting at the given node.
    Node* copyNode(Node* node) {
        if (!node) {
            return nullptr;
        }
        Node *newNode = makeNode(node->key, node->value);
        newNode->left = copyNode(node->left);
        newNode->right = copyNode(node->right);
        return newNode;
    }

    // Performs a guided search of the subtree at the given node. At each level,
    // shouldGoRight is queried to determine whether the left or right subtree
    // should be searched. Searching stops when isFound returns true, at which
    // point the current node's value is returned.
    const V& search(
        Node* node,
        std::function<bool(const K& key, const V& value)> isFound,
        std::function<bool(const K& key, const V& value)> shouldGoRight) const {
        if (!node) {
            throw std::runtime_error("Value not found");
        }

        if (isFound(node->key, node->value)) {
            return node->value;
        }

        if (shouldGoRight(node->key, node->value)) {
            return search(node->right, isFound, shouldGoRight);
        } else {
            return search(node->left, isFound, shouldGoRight);
        }
    }

public:

    // Constructs an empty subtree.
    BinarySearchTree() {
        root = nullptr;
    }

    // Initializes the BST as a duplicate of the given one.
    BinarySearchTree(const BinarySearchTree<K,V>& other) {
        root = copyNode(other.root);
    }

    // Initializes the BST as a single node containing the given
    // key and value.    
    BinarySearchTree(const K& key, const V& value) {
        root = makeNode(key, value);
    }

    // Initializes the BST so that the root contains the given key and
    // value with its left and right children as copies of the given
    // left and right trees.
    BinarySearchTree(const K& key, const V& value, const BinarySearchTree<K,V>& left, const BinarySearchTree<K,V>& right) {
        root = makeNode(key, value);
        root->left = copyNode(left.root);
        root->right = copyNode(right.root);
    }

    // Performs a copy assignment from the given tree to this one.
    void operator=(const BinarySearchTree<K,V> &other) {
        deleteTree(root);
        root = copyNode(other.root);
    }

    // Frees all memory allocated by the tree.    
    ~BinarySearchTree() {
        deleteTree(root);
    }

    // Performs an "upsert": If the given key already exists, its value
    // is replaced with the given one, otherwise a new key/value is added.
    void put(const K& key, const V& value) {
        if (!root) {
            root = makeNode(key, value);
        } else {
            put(key, value, root);
        }
    }

    // Searches for the key in the tree. The key must exist, otherwise an
    // exception is thrown.
    const V& get(const K& key) const {
        return get(key, root);
    }

    // Returns the key-value pair at the root of the tree, or throws an
    // exception if the tree is empty.
    std::pair<K,V> getRoot() const {
        if (!root) {
            throw std::runtime_error("Tree is empty");
        }

        return std::make_pair(root->key, root->value);
    }

    // Returns true if the given key exists in the tree.
    bool exists(const K& key) const {
        return exists(key, root);
    }

    // Performs an inorder traversal of the tree. Invokes the given lambda
    // at each node.
    void traverseInorder(std::function<void(const K&, const V&)> visit) {
        traverseInorder(root, visit);
    }

    // Performs a preorder traversal of the tree. Invokes the appropriate lambdas
    // before and after each descent. Halts the traversal if the shouldStop lambda
    // returns true.
    void traversePreorder(std::function<bool(const K& key, const V& value)> shouldStop,
                          std::function<void(void)> beginLeft,
                          std::function<void(void)> endLeft,
                          std::function<void(void)> beginRight,
                          std::function<void(void)> endRight) const {
        traversePreorder(root, shouldStop, beginLeft, endLeft, beginRight, endRight);
    }

    // Performs a guided search of the tree. At each level, shouldGoRight is queried
    // to determine whether the left or right subtree should be searched. Searching
    // stops when isFound returns true, at which point the current node's value is
    // returned.
    const V& search(
        std::function<bool(const K& key, const V& value)> isFound,
        std::function<bool(const K& key, const V& value)> shouldGoRight) const {
        return search(root, isFound, shouldGoRight);
    }

    // Converts the tree to a DOT-formatted string.
    std::string toDOT() const {
        std::stringstream out;

        out << "digraph G {" << std::endl;

        int id = 1;
        if (root) {
            writeDOT(root, out, id);
        }

        out << "}" << std::endl;

        return out.str();
    }
};
