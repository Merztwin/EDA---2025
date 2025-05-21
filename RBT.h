#pragma once
#include <iostream>

// Node structure for the Red-Black Tree
struct Node {
    int data;
    std::string color;
    Node *left, *right, *parent;

    Node(int data)
        : data(data)
        , color("RED")
        , left(nullptr)
        , right(nullptr)
        , parent(nullptr)
    {
    }
};

// Red-Black Tree class
class RedBlackTree {
private:
    Node* root;
    Node* NIL;

    // Utility function to perform left rotation
    void leftRotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Utility function to perform right rotation
    void rightRotate(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* k)
    {
        while (k != root && k->parent->color == "RED") {
            if (k->parent == k->parent->parent->left) {
                Node* u = k->parent->parent->right; // uncle
                if (u->color == "RED") {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    rightRotate(k->parent->parent);
                }
            }
            else {
                Node* u = k->parent->parent->left; // uncle
                if (u->color == "RED") {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                }
                else {
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

    void traversalHelper(Node* node)
    {
        if (node != NIL) {
            traversalHelper(node->left);
            std::cout << node->data << " ";
            traversalHelper(node->right);
        }
    }

    // Search helper function
    Node* searchHelper(Node* node, int data)
    {
        if (node == NIL || data == node->data) {
            return node;
        }
        if (data < node->data) {
            return searchHelper(node->left, data);
        }
        return searchHelper(node->right, data);
    }

public:
    // Constructor
    RedBlackTree()
    {
        NIL = new Node(0);
        NIL->color = "BLACK";
        NIL->left = NIL->right = NIL;
        root = NIL;
    }

    // Insert function
    void insert(int data)
    {
        Node* new_node = new Node(data);
        new_node->left = NIL;
        new_node->right = NIL;

        Node* parent = nullptr;
        Node* current = root;

        // BST insert
        while (current != NIL) {
            parent = current;
            if (new_node->data < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        new_node->parent = parent;

        if (parent == nullptr) {
            root = new_node;
        }
        else if (new_node->data < parent->data) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }

        if (new_node->parent == nullptr) {
            new_node->color = "BLACK";
            return;
        }

        if (new_node->parent->parent == nullptr) {
            return;
        }

        fixInsert(new_node);
    }

    // traversal traversal
    void traversal() 
    { 
        traversalHelper(root);
        std::cout << std::endl;
    }

    // Search function
    Node* search(int data)
    {
        return searchHelper(root, data);
    }
};