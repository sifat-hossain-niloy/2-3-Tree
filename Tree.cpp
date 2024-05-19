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

    string temp;
    if (value < node->small) {
        leftChild->small = value;
        temp = node->small;
    } else if (value > node->large) {
        rightChild->small = value;
        temp = node->large;
    } else {
        temp = value;
    }
    // so far checked


    if (node->left) {
        leftChild->left = node->left;
        leftChild->middle = node->middle;
        // rightChild->left = node->middle;
        rightChild->middle = node->right;
        

        if (leftChild->left) leftChild->left->parent = leftChild;
        if (leftChild->middle) leftChild->middle->parent = leftChild;
        // if (rightChild->left) rightChild->left->parent = rightChild;
        if (rightChild->middle) rightChild->middle->parent = rightChild;
    }

    if (node == root) {// checked
        root = new Node(temp);
        root->left = leftChild;
        leftChild->parent = root;
        
        root->middle = rightChild;
        rightChild->parent = root;
        delete node;
    } else {
        Node *parent = node->parent;

        if (parent->hasTwoKeys()) {
            split(parent, temp);

            if (parent->left == node){
                Node *nowParent = node->parent;

                nowParent->left = leftChild;
                nowParent->right = rightChild;
                leftChild->parent = nowParent;
                rightChild->parent = nowParent;
                
            } else if (parent->middle == node) {
                // cout << "asddfs";
                Node *nowParent = node->parent;

                nowParent->middle = leftChild;
                leftChild->parent = nowParent;

                parent->right->parent->left = rightChild;
                rightChild->parent = parent->right->parent;


            } else {
                Node *nowParent = node->parent;

                nowParent->left = leftChild;
                leftChild->parent=nowParent;

                nowParent->middle = rightChild;
                rightChild->parent = nowParent;
            }
        } else {
            if (parent->left == node) {//checked

                parent->large = parent->small;
                parent->small = temp;

                parent->right = parent->middle;
                parent->right->parent = parent;

                parent->middle = rightChild;
                rightChild->parent = parent;

                parent->left = leftChild;
                leftChild->parent = parent;

            } else {//checked

                parent->large = temp;
                
                parent->middle = leftChild;
                leftChild->parent = parent;

                parent->right = rightChild;
                rightChild->parent = parent;

            }
            delete node;
        }
    }
}

void Tree::remove(const string &value) {
    remove(root, value);
    if (root && root->isLeaf() && root->small.empty()) {
        delete root;
        root = nullptr;
    }
}

void Tree::remove(Node *node, const string &value) {
    if (!node) return;

    if (node->isLeaf()) {
        if (node->small == value) {
            // cout << "ekhane 3 ";
            node->small = "";
            if(!node->large.empty())
            {
                node->small = node->large;
                node->large = "";
            }
        } else if (node->large == value) {
            node->large = "";
        }
        if (node->small.empty() && node->large.empty()) {
            fix(node);
        }
        return;
    }

    if (value < node->small) {
        remove(node->left, value);
    } else if (node->hasTwoKeys() &&  value >  node->large ) {
        remove(node->right, value);
    }
    else if(value >node->small)
    {
        remove(node->middle, value);
    } else {
        Node *replaceNode = getInOrderSuccessor(node);
        if (replaceNode) {
            if (node->small == value) {
                node->small = replaceNode->small;
                remove(node->left, replaceNode->small);
            } else {
                node->large = replaceNode->small;
                remove(node->middle, replaceNode->small);
            }
        }
    }
}

void Tree::fix(Node *node) {
    if (!node || node->hasTwoKeys() || node == root) return;

    Node *parent = node->parent;
    if (!parent) {
        if (!node->small.empty() && !node->large.empty()) {
            root = node;
        } else {
            delete node;
            root = nullptr;
        }
        return;
    }

    if (parent->left == node) {
        Node *sibling = parent->middle;
        if (sibling->hasTwoKeys()) {
            node->small = parent->small;
            parent->small = sibling->small;
            sibling->small = sibling->large;
            sibling->large = "";
        } else {

            
            node->small = parent->small;
            parent->small = sibling->small;
            remove(sibling,sibling->small);
        }
    } else if (parent->middle == node) {
        Node *sibling = parent->left;
        if (sibling->hasTwoKeys()) {
            // cout << "ekhane 2 ";

            //checked
            node->small = parent->small;
            parent->small = sibling->large;
            sibling->large = "";

            node->middle = node->left;
            node->left = sibling->right;
            sibling->right = nullptr;
            if (node->left) node->left->parent = node;

        } else {
            // cout << "ekhane ";

            // parent->large = parent->small;

            //checked
            sibling->large= parent->small;
            parent->small = parent->large;
            parent->large = "";
            delete node;
            parent->middle = parent->right;
            parent->right = nullptr;

        }
    } else {
        Node *sibling = parent->middle;
        if (sibling->hasTwoKeys()) {
            node->small = parent->large;
            parent->large = sibling->large;
            sibling->large = "";
            node->middle = node->left;
            node->left = sibling->right;
            sibling->right = nullptr;
            if (node->left) node->left->parent = node;
        } else {
            delete node;
            parent->right = nullptr;
            sibling->large = parent->large;
            parent->large = "";
        }
    }
    fix(parent);
}

Node* Tree::getInOrderSuccessor(Node *node) {
    Node *current = node->right;
    while (current && !current->isLeaf()) {
        current = current->left ? current->left : current->middle;
    }
    return current;
}

void Tree::preOrder() const {
    preOrder(root);
    cout << endl;
}

void Tree::preOrder(Node *node) const {
    if (!node) return;

    if (!node->small.empty()) cout << node->small << ", ";

    preOrder(node->left);
    if (!node->large.empty()) cout << node->large << ", ";

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
    if (!node->small.empty()) cout << node->small << ", ";

    postOrder(node->right);

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