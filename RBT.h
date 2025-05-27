#pragma once
#include <iostream>
#include <string>
#include <climits>

struct Node {
    int data;
    std::string color;
    Node *left, *right, *parent;

    Node(int data)
        : data(data), color("RED"), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* k) {
        while (k != root && k->parent->color == "RED") {
            if (k->parent == k->parent->parent->left) {
                Node* u = k->parent->parent->right;
                if (u->color == "RED") {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    rightRotate(k->parent->parent);
                }
            } else {
                Node* u = k->parent->parent->left;
                if (u->color == "RED") {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = "BLACK";
    }

    void inOrderHelper(Node* node, int depth, std::ostream& out) {
        if (node != NIL) {
            inOrderHelper(node->left, depth + 1, out);
            out << node->data << "," << depth << "," << node->color[0] << " ";
            inOrderHelper(node->right, depth + 1, out);
        }
    }

    Node* searchHelper(Node* node, int data) {
        if (node == NIL || data == node->data) return node;
        if (data < node->data) return searchHelper(node->left, data);
        return searchHelper(node->right, data);
    }

public:
    RedBlackTree() {
        NIL = new Node(0);
        NIL->color = "BLACK";
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    void insert(int data) {
        Node* new_node = new Node(data);
        new_node->left = NIL;
        new_node->right = NIL;

        Node* parent = nullptr;
        Node* current = root;

        while (current != NIL) {
            parent = current;
            if (new_node->data < current->data) current = current->left;
            else current = current->right;
        }

        new_node->parent = parent;
        if (parent == nullptr) root = new_node;
        else if (new_node->data < parent->data) parent->left = new_node;
        else parent->right = new_node;

        if (new_node->parent == nullptr) {
            new_node->color = "BLACK";
            return;
        }

        if (new_node->parent->parent == nullptr) return;

        fixInsert(new_node);
    }

    int findSuccessor(int x) {
        Node* current = root;
        Node* successor = nullptr;
        while (current != NIL) {
            if (current->data > x) {
                successor = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return (successor != nullptr) ? successor->data : INT_MAX;
    }

    void printTreeWithDepthAndColor(std::ostream& out) {
        inOrderHelper(root, 0, out);
        out << "\n";
    }

    Node* getRoot() { return root; }
    Node* getNIL() { return NIL; }
    void setRoot(Node* r) { root = r; }
};
