#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
    Node *root;

public:
    Tree();
    ~Tree();
    void insert(const string &);
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void remove(const string &);
    bool search(const string &) const;

private:
    void destroyTree(Node *node);
    void insert(Node *node, const string &value);
    void split(Node *node,const string &value);
    void preOrder(Node *node) const;
    void inOrder(Node *node) const;
    void postOrder(Node *node) const;
    bool search(Node *node, const string &value) const;
    void remove(Node *node, const string &value);
    void fix(Node *node);
    Node* getInOrderSuccessor(Node *node);
};

#endif