#pragma once

#include <sys/types.h>
class Node 
{
    private:
        int key;
        u_int8_t color; // red = 0; black = 1; 
        Node *left, *right, *parent;

    public:
        Node(int key);
        ~Node();

        Node(int key, Node* parent);

};

class RedBlackTree
{
	
};