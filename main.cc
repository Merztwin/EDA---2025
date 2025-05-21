// #include "RedBlackTree.hh"
#include "RBT.h"

//std
#include <iostream>

//main
int main()
{
    RedBlackTree rbt;

    // Inserting elements
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);

    rbt.traversal();
    
    std::cout << "Hello World! \n";
    return EXIT_SUCCESS;
}


