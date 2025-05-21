#include "RedBlackTree.hh"
#include <sys/types.h>


Node::Node(int key)
{
    this->key = key;
    this->color = 0; // red = 0; black = 1; 
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

Node::Node(int key, Node* parent)
{
    this->key = key;
    this->color = 0; // red = 0; black = 1; 
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
}
