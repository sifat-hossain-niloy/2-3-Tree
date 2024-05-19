#include "Node.h"

// Node constructor
Node::Node(const string &value) : small(value), large(""), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}

// Utility function to check if the node is a leaf
bool Node::isLeaf() const {
    return left == nullptr && middle == nullptr && right == nullptr;
}

// Utility function to check if the node has two keys
bool Node::hasTwoKeys() const {
    return !large.empty();
}