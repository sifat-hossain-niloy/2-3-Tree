#include "Tree.h"
#include <iostream>

using namespace std;

// Tree constructor
Tree::Tree() : root(nullptr) {}

// Tree destructor
Tree::~Tree() {
    destroyTree(root);
}

void Tree::destroyTree(Node *node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->middle);
        destroyTree(node->right);
        delete node;
    }
}

// // Insert function
// void Tree::insert(const string &value) {
//     if (!root) {
//         root = new Node(value);
//     } else {
//         insert(root, value);
//     }
// }

// void Tree::insert(Node *node, const string &value) {
//     if (node->isLeaf()) {
//         if (node->hasTwoKeys()) {
//             string temp = value;
//             // Split the node
//             if (value < node->small) {
//                 temp = node->small;
//                 node->small = value;
//             } else if (value > node->large) {
//                 temp = node->large;
//                 node->large = value;
//             }
//             split(node, temp);
//         } else {
//             // Insert into a leaf with one key
//             if (value < node->small) {
//                 node->large = node->small;
//                 node->small = value;
//             } else {
//                 node->large = value;
//             }
//         }
//     } else {
//         // Traverse to the appropriate child
//         if (value < node->small) {
//             insert(node->left, value);
//         } else if (!node->large.empty() && value > node->large) {
//             insert(node->right, value);
//         } else {
//             insert(node->middle, value);
//         }
//     }
// }

// void Tree::split(Node *node, const string &value) {
//     if (node == root) {
//         // Split the root
//         Node *leftChild = new Node(node->small);
//         Node *rightChild = new Node(node->large);

//         leftChild->left = node->left;
//         leftChild->middle = node->middle;
//         rightChild->left = node->middle;
//         rightChild->middle = node->right;

//         if (leftChild->left) leftChild->left->parent = leftChild;
//         if (leftChild->middle) leftChild->middle->parent = leftChild;
//         if (rightChild->left) rightChild->left->parent = rightChild;
//         if (rightChild->middle) rightChild->middle->parent = rightChild;

//         root = new Node(value);
//         root->left = leftChild;
//         root->middle = rightChild;

//         leftChild->parent = root;
//         rightChild->parent = root;

//         delete node;
//     } else {
//         // Split an internal node
//         Node *parent = node->parent;
//         Node *newNode = new Node(value);

//         newNode->left = node->middle;
//         newNode->middle = node->right;
//         if (newNode->left) newNode->left->parent = newNode;
//         if (newNode->middle) newNode->middle->parent = newNode;

//         if (parent->hasTwoKeys()) {
//             // Parent needs to be split
//             if (node == parent->left) {
//                 parent->left = newNode;
//                 parent->middle = newNode;
//             } else if (node == parent->middle) {
//                 parent->middle = newNode;
//             } else {
//                 parent->right = newNode;
//             }
//             split(parent, value);
//         } else {
//             // Insert into parent
//             if (node == parent->left) {
//                 parent->large = parent->small;
//                 parent->small = node->small;
//                 parent->middle = newNode;
//             } else {
//                 parent->large = node->small;
//                 parent->middle = newNode;
//             }
//             newNode->parent = parent;
//         }

//         delete node;
//     }
// }

void Tree::insert(const string &value) {
    if (!root) {
        root = new Node(value);
    } else {
        insert(root, value);
    }
}

void Tree::insert(Node *node, const string &value) {
    if (node->isLeaf()) {
        if (node->hasTwoKeys()) {
            // Split the node
            split(node, value);
        } else {
            // Insert into a leaf with one key
            if (value < node->small) {
                node->large = node->small;
                node->small = value;
            } else {
                node->large = value;
            }
        }
    } else {
        // Traverse to the appropriate child
        if (value < node->small) {
            insert(node->left, value);
        } else if (!node->large.empty() && value > node->large) {
            insert(node->right, value);
        } else {
            insert(node->middle, value);
        }
    }
}

void Tree::split(Node *node, const string &value) {
    Node *leftChild = new Node(node->small);
    Node *rightChild = new Node(node->large);

    if (value < node->small) {
        leftChild->small = value;
    } else if (value > node->large) {
        rightChild->small = value;
    } else {
        node->small = value;
    }

    if (node->left) {
        leftChild->left = node->left;
        leftChild->middle = node->middle;
        rightChild->left = node->middle;
        rightChild->middle = node->right;

        if (leftChild->left) leftChild->left->parent = leftChild;
        if (leftChild->middle) leftChild->middle->parent = leftChild;
        if (rightChild->left) rightChild->left->parent = rightChild;
        if (rightChild->middle) rightChild->middle->parent = rightChild;
    }

    if (node == root) {
        root = new Node(node->small);
        root->left = leftChild;
        root->middle = rightChild;
        leftChild->parent = root;
        rightChild->parent = root;
        delete node;
    } else {
        Node *parent = node->parent;
        if (parent->hasTwoKeys()) {
            split(parent, node->small);
            if (parent->left == node) {
                parent->left = leftChild;
                parent->middle = rightChild;
            } else if (parent->middle == node) {
                parent->middle = leftChild;
                parent->right = rightChild;
            } else {
                parent->right = rightChild;
            }
        } else {
            if (parent->left == node) {
                parent->large = parent->small;
                parent->small = node->small;
                parent->middle = rightChild;
            } else {
                parent->large = node->small;
                parent->middle = leftChild;
                parent->right = rightChild;
            }
            leftChild->parent = parent;
            rightChild->parent = parent;
            delete node;
        }
    }
}

// Revised remove and fix functions
void Tree::remove(const string &value) {
    remove(root, value);
}
void Tree::remove(Node *node, const string &value) {
    if (!node) return;

    if (node->isLeaf()) {
        if (node->small == value) {
            node->small = node->large;
            node->large.clear();
        } else if (node->large == value) {
            node->large.clear();
        }
        fix(node);
    } else {
        if (node->small == value) {
            Node *predecessor = getInOrderPredecessor(node->left);
            node->small = predecessor->small;
            remove(predecessor, predecessor->small);
        } else if (node->large == value) {
            Node *predecessor = getInOrderPredecessor(node->middle);
            node->large = predecessor->small;
            remove(predecessor, predecessor->small);
        } else if (value < node->small) {
            remove(node->left, value);
        } else if (!node->large.empty() && value > node->large) {
            remove(node->right, value);
        } else {
            remove(node->middle, value);
        }
    }
}


Node* Tree::getInOrderPredecessor(Node *node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}
void Tree::fix(Node *node) {
    if (node == root) {
        if (root->small.empty()) {
            if (root->left) {
                Node *oldRoot = root;
                root = root->left;
                root->parent = nullptr;
                delete oldRoot;
            } else if (root->middle) {
                Node *oldRoot = root;
                root = root->middle;
                root->parent = nullptr;
                delete oldRoot;
            } else if (root->right) {
                Node *oldRoot = root;
                root = root->right;
                root->parent = nullptr;
                delete oldRoot;
            } else {
                delete root;
                root = nullptr;
            }
        }
        return;
    }

    if (!node->small.empty()) {
        return;
    }

    Node *parent = node->parent;
    if (node == parent->left) {
        if (parent->middle && parent->middle->hasTwoKeys()) {
            node->small = parent->small;
            parent->small = parent->middle->small;
            parent->middle->small = parent->middle->large;
            parent->middle->large.clear();
        } else if (parent->middle) {
            node->small = parent->small;
            node->large = parent->middle->small;
            delete parent->middle;
            parent->middle = nullptr;
            fix(parent);
        } else if (parent->right && parent->right->hasTwoKeys()) {
            node->small = parent->small;
            parent->small = parent->right->small;
            parent->right->small = parent->right->large;
            parent->right->large.clear();
        } else {
            node->small = parent->small;
            if (parent->middle) {
                node->large = parent->middle->small;
                delete parent->middle;
                parent->middle = nullptr;
            } else if (parent->right) {
                node->large = parent->right->small;
                delete parent->right;
                parent->right = nullptr;
            }
            fix(parent);
        }
    } else if (node == parent->middle) {
        if (parent->left->hasTwoKeys()) {
            node->small = parent->small;
            parent->small = parent->left->large;
            parent->left->large.clear();
        } else {
            node->small = parent->small;
            if (parent->right && parent->right->hasTwoKeys()) {
                parent->small = parent->right->small;
                parent->right->small = parent->right->large;
                parent->right->large.clear();
            } else {
                delete parent->left;
                parent->left = node;
                parent->middle = nullptr;
                fix(parent);
            }
        }
    } else {
        if (parent->middle->hasTwoKeys()) {
            node->small = parent->large;
            parent->large = parent->middle->large;
            parent->middle->large.clear();
        } else {
            node->small = parent->large;
            delete parent->middle;
            parent->middle = node;
            parent->right = nullptr;
            fix(parent);
        }
    }
}

void Tree::preOrder() const {
    preOrder(root);
    cout << endl;
}

void Tree::preOrder(Node *node) const {
    if (!node) return;

    if (!node->small.empty()) cout << node->small << ", ";
    if (!node->large.empty()) cout << node->large << ", ";

    preOrder(node->left);
    preOrder(node->middle);
    preOrder(node->right);
}

void Tree::inOrder() const {
    inOrder(root);
    cout << endl;
}

void Tree::inOrder(Node *node) const {
    if (!node) return;

    inOrder(node->left);
    if (!node->small.empty()) cout << node->small << ", ";
    inOrder(node->middle);
    if (!node->large.empty()) cout << node->large << ", ";
    inOrder(node->right);
}

void Tree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void Tree::postOrder(Node *node) const {
    if (!node) return;

    postOrder(node->left);
    postOrder(node->middle);
    postOrder(node->right);

    if (!node->small.empty()) cout << node->small << ", ";
    if (!node->large.empty()) cout << node->large << ", ";
}

// Search function
bool Tree::search(const string &value) const {
    return search(root, value);
}

bool Tree::search(Node *node, const string &value) const {
    if (!node) {
        return false;
    }

    if (node->small == value || node->large == value) {
        return true;
    }

    if (value < node->small) {
        return search(node->left, value);
    } else if (!node->large.empty() && value > node->large) {
        return search(node->right, value);
    } else {
        return search(node->middle, value);
    }
}

