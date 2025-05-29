#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <limits>

class Node {
    public:
        int data;
        std::string color;
        Node *left, *right, *parent;

        Node(int data) : data(data), color("R"), left(nullptr), right(nullptr), parent(nullptr) 
        {

        }

        Node(Node& oldNode)
        {
            data = oldNode.data;
            color = oldNode.color;

            left = oldNode.left;
            right = oldNode.right;
            parent = oldNode.parent;
        }
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;
    int current_ver = 0;
    Node* versions[100];
    

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left->data != -1) y->left->parent = x;
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
        if (y->right->data != -1) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* k) {
        while (k != root && k->parent->color == "R") {
            if (k->parent == k->parent->parent->left) {
                Node* u = new Node(*k->parent->parent->right);
                k->parent->parent->right = u;

                if (u->color == "R") {
                    k->parent->color = "N";
                    u->color = "N";
                    k->parent->parent->color = "R";
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = "N";
                    k->parent->parent->color = "R";
                    rightRotate(k->parent->parent);
                }
            } else {
                Node* u = new Node(*k->parent->parent->left);
                k->parent->parent->left = u;

                if (u->color == "R") {
                    k->parent->color = "N";
                    u->color = "N";
                    k->parent->parent->color = "R";
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = "N";
                    k->parent->parent->color = "R";
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = "N";
    }

    void fixDelete(Node* x) {
        while (x != root && x->color == "N") {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == "R") {
                    w->color = "N";
                    x->parent->color = "R";
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == "N" && w->right->color == "N") {
                    w->color = "R";
                    x = x->parent;
                } else {
                    if (w->right->color == "N") {
                        w->left->color = "N";
                        w->color = "R";
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = "N";
                    w->right->color = "N";
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == "R") {
                    w->color = "N";
                    x->parent->color = "R";
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == "N" && w->left->color == "N") {
                    w->color = "R";
                    x = x->parent;
                } else {
                    if (w->left->color == "N") {
                        w->right->color = "N";
                        w->color = "R";
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = "N";
                    w->left->color = "N";
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = "N";
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    Node* minimum(Node* node) {
        while (node->left->data != -1) node = node->left;
        return node;
    }

    void deleteNode(Node* z) {
        Node* y = z;
        Node* x;
        std::string y_original_color = y->color;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (y_original_color == "N") {
            fixDelete(x);
        }
        delete z;
    }

    void inOrderHelper(Node* node, int depth, std::ostream& out) {
        if (node->data != -1) {
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

    Node* findRoot(Node* current) {
       while (current->parent != nullptr) {
            current = current->parent;
        }
        return current;
    }

public:
    RedBlackTree() {
        NIL = new Node(-1);
        NIL->color = "N";
        NIL->left = NIL->right = NIL;
        root = NIL;
        std::fill_n(versions, 100, NIL);
    }

    void insert(int data) {
        if (current_ver == 99) {
            std::cout << "limite de versões atingido \n";
            return;
        }

        current_ver++;
        Node* new_node = new Node(data);
        new_node->left = NIL;
        new_node->right = NIL;

        Node* parent = nullptr;
        // Node* current = root;

        Node* current;
        if (root != NIL) {
            current = new Node(*root);
            current->parent = nullptr;
        }
        else {
            current = root;
        }

        while (current->data != -1) {
            parent = current;

            if (new_node->data < current->data) {
                // current = current->left;

                Node* mod_left = new Node(*current->left);
                mod_left->parent = current;
                current->left = mod_left;
                current = current->left;
                // if(current->left != NIL) {
                //     Node* mod_left = new Node(*current->left);
                //     mod_left->parent = current;
                //     current = mod_left;
                // }
                // else {
                //     current = current->left;
                // }

            }
            else {
                // current = current->right;
                Node* mod_right = new Node(*current->right);
                mod_right->parent = current;
                current->right = mod_right;
                current = current->right;
                // if(current->right != NIL) {
                //     Node* mod_right = new Node(*current->right);
                //     mod_right->parent = current;
                //     current = mod_right;
                // }
                // else {
                //     current = current->right;
                // }

            }
        }

        // std::cout << parent->data << "\n";
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
            new_node->color = "N";
            versions[current_ver] = root;
            return;
        }

        if (new_node->parent->parent == nullptr) {

            root = findRoot(new_node);
            versions[current_ver] = root;
            return;
        }

        root = findRoot(new_node);
        fixInsert(new_node);
        versions[current_ver] = root;
    }

    void remove(int data) {
        if (current_ver == 99) {
            std::cout << "limite de versões atingido \n";
            return;
        }

        Node* node = searchHelper(root, data);
        if (node != NIL) deleteNode(node);
        // current_ver++;
        // for(int i=current_ver;i<100;i++)
        // {
        //     versions[i] = root;
        // }
    }

    void findSuccessor(std::ostream& out, int x, int rbtVersion) {
        Node* current;
        if (rbtVersion > current_ver) current = versions[current_ver];
        else current = versions[rbtVersion];

        Node* successor = nullptr;
        while (current->data != -1) {
            if (current->data > x) {
                successor = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        out << ((successor != nullptr) ? std::to_string(successor->data) : "inf") << "\n\n";
    }

    void printTreeWithDepthAndColor(std::ostream& out, int rbtVersion) {
        Node* current;
        if (rbtVersion > current_ver) current = versions[current_ver];
        else current = versions[rbtVersion];
        out << "IMP " << rbtVersion << " \n";
        if (current->data==-1) out << "NULL";
        inOrderHelper(current, 0, out);
        out << "\n\n";
    }

    Node* getRoot() { return root; }
    Node* getNIL() { return NIL; }
    void setRoot(Node* r) { root = r; }
};
