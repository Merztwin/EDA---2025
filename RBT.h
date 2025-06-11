#pragma once
#include <algorithm>
#include <iostream>
#include <string>


class RedBlackTree
{
    private:
        enum State
        {
            notModified,
            leftModified,
            rightModified,
            nilState
        };

        enum Color : char
        {
            R = 'R', 
            N = 'N'
        };


        struct Node
        {
            int timestamp = 0;
            int data;
            Color color;
            State state = notModified;
            Node *left, *right, *parent, *nilPointer;

            Node(int data) : data(data), color(R), left(nullptr), right(nullptr), parent(nullptr), nilPointer(nullptr) {}

            Node(Node& oldNode)
            {
                data = oldNode.data;
                color = oldNode.color;

                left = oldNode.left;
                right = oldNode.right;
                parent = oldNode.parent;
                state = notModified;
                timestamp = 0;
            }
        };


        Node* root;
        Node* NIL;

        Node* versions[100];
        int currentVer = 0;


        Node* copyNode(Node* oldNode)
        {
            if (oldNode->state != nilState) return new Node(*oldNode);
            else return oldNode;
        }

        void leftRotate(Node* x)
        {
            Node* y = x->right;
            x->right = y->left;

            if (y->left->state != nilState) y->left->parent = x;
            y->parent = x->parent;

            if (x->parent == nullptr) root = y;
            else if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;

            y->left = x;
            x->parent = y;
        }

        void rightRotate(Node* x)
        {
            Node* y = x->left;
            x->left = y->right;

            if (y->right->state != nilState) y->right->parent = x;
            y->parent = x->parent;

            if (x->parent == nullptr) root = y;
            else if (x == x->parent->right) x->parent->right = y;
            else x->parent->left = y;

            y->right = x;
            x->parent = y;
        }

        void fixInsert(Node* k)
        {
            while (k != root && k->parent->color == R)
            {
                if (k->parent == k->parent->parent->left)
                {
                    Node* u = copyNode(k->parent->parent->right);
                    k->parent->parent->right = u;

                    if (u->color == R)
                    {
                        k->parent->color = N;
                        u->color = N;

                        k->parent->parent->color = R;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->right)
                        {
                            k = k->parent;
                            leftRotate(k);
                        }

                        k->parent->color = N;
                        k->parent->parent->color = R;
                        rightRotate(k->parent->parent);
                    }
                }
                else
                {
                    Node* u = copyNode(k->parent->parent->left);
                    k->parent->parent->left = u;

                    if (u->color == R)
                    {
                        k->parent->color = N;
                        u->color = N;

                        k->parent->parent->color = R;
                        k = k->parent->parent;
                    }
                    else
                    {
                        if (k == k->parent->left)
                        {
                            k = k->parent;
                            rightRotate(k);
                        }

                        k->parent->color = N;
                        k->parent->parent->color = R;
                        leftRotate(k->parent->parent);
                    }
                }
            }

            root->color = N;
        }

        void fixDelete(Node* x)
        {
            while (x != root && x->color == N)
            {
                if (x->data == x->parent->left->data)
                {
                    Node* w = copyNode(x->parent->right);
                    if (w->color == R)
                    {
                        w->color = N;
                        x->parent->color = R;

                        leftRotate(x->parent);
                        w = x->parent->right;
                    }
                    if (w->left->color == N && w->right->color == N)
                    {
                        w->color = R;
                        x = x->parent;
                    }
                    else
                    {
                        if (w->right->color == N)
                        {
                            w->left->color = N;
                            w->color = R;

                            rightRotate(w);
                            w = x->parent->right;
                        }

                        w->color = x->parent->color;
                        x->parent->color = N;
                        w->right->color = N;

                        leftRotate(x->parent);
                        x = root;
                    }
                }
                else
                {
                    Node* w = copyNode(x->parent->left);
                    if (w->color == R)
                    {
                        w->color = N;
                        x->parent->color = R;

                        rightRotate(x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == N && w->left->color == N)
                    {
                        w->color = R;
                        x = x->parent;
                    }
                    else
                    {
                        if (w->left->color == N)
                        {
                            w->right->color = N;
                            w->color = R;

                            leftRotate(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = N;
                        w->left->color = N;

                        rightRotate(x->parent);
                        x = root;
                    }
                }
            }

            x->color = N;
        }

        void transplant(Node* u, Node* v)
        {
            if (u->parent == nullptr) root = v;
            else if (u->data == u->parent->left->data) u->parent->left = v;
            else u->parent->right = v;

            v->parent = u->parent;
        }

        Node* minimum(Node* node)
        {
            while (node->left->state != nilState) node = node->left;
            return node;
        }

        void deleteNode(Node* z)
        {
            Node* y = z;
            Node* x;

            Color y_original_color = y->color;
            if (z->left->state == nilState)
            {
                x = z->right;
                transplant(z, z->right);
            }
            else if (z->right == NIL)
            {
                x = z->left;
                transplant(z, z->left);
            }
            else
            {
                y = copyNode(z->right);
                z->right = y;

                while (y->left->state != nilState)
                {
                    Node* mod_left = copyNode(y->left);
                    mod_left->parent = y;

                    y->left = mod_left;
                    y = y->left;
                }

                Node* parent =  y->parent;
                y_original_color = y->color;

                x = copyNode(y->right);
                x->parent = y;

                if (y->parent->data == z->data) x->parent = y;
                else 
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;

                y->color = z->color;
            }

            if (y_original_color == N) fixDelete(x);
            delete z;
        }

        void inOrderHelper(Node* node, int depth, std::ostream& out, int timestamp)
        {
            if (node->timestamp > timestamp)
            {
                if (node->data != -1)
                {
                    if (node->state != leftModified)
                    {
                        inOrderHelper(node->left, depth + 1, out, timestamp);
                        if (node->left->data != -1) out << " ";
                    }

                    out << node->data << "," << depth << "," << node->color;

                    if (node->state != rightModified)
                    {
                        if (node->right->data != -1) out << " ";
                        inOrderHelper(node->right, depth + 1, out, timestamp);
                    }
                }
            }
            else
            {
                if (node->data != -1)
                {
                    inOrderHelper(node->left, depth + 1, out, timestamp);

                    if (node->left->data != -1) out << " ";
                    out << node->data << "," << depth << "," << node->color;

                    if (node->right->data != -1) out << " ";
                    inOrderHelper(node->right, depth + 1, out, timestamp);
                }
            }
        }

        Node* searchHelper(Node* node, int data)
        {
            if (node == NIL || data == node->data) return node;
            if (data < node->data) return searchHelper(node->left, data);

            return searchHelper(node->right, data);
        }

        Node* findRoot(Node* current)
        {
            while (current->parent != nullptr) current = current->parent;
            return current;
        }

    public:
        RedBlackTree()
        {
            NIL = new Node(-1);

            NIL->color = N;
            NIL->left = NIL->right = NIL->nilPointer = NIL;
            NIL->state = nilState;

            root = NIL;
            std::fill_n(versions, 100, NIL);
        }

        void insert(int data)
        {
            if (currentVer == 99) 
            {
                std::cout << "limite de versões atingido\n";
                return;
            }

            currentVer++;
            if (searchHelper(root, data) != NIL)
            {
                std::cout << "Chave já existe\n";
                versions[currentVer] = root;
                return;
            }

            Node* newNode = new Node(data);
            newNode->left = newNode->right = newNode->nilPointer = NIL;

            Node* parent = nullptr;
            Node* current = root;

            while (current->state != nilState)
            {
                parent = current;
                if (newNode->data < current->data) current = current->left;
                else current = current->right;
            }

            if (parent == nullptr)
            {
                root = newNode;
                newNode->color = N;
                versions[currentVer] = root;
                return;
            }

            if ((parent->state == notModified) && (parent->color == N))
            {
                if (newNode->data < parent->data)
                {
                    parent->state = leftModified;
                    parent->timestamp = currentVer;
                    parent->left = newNode;
                    newNode->parent = parent;
                }
                else 
                {
                    parent->state = rightModified;
                    parent->timestamp = currentVer;
                    parent->right = newNode;
                    newNode->parent = parent;
                }

                versions[currentVer] = root;
                return;
            }


            if (root != NIL)
            {
                current = copyNode(root);
                current->parent = nullptr;
            }

            while (current->state != nilState)
            {
                parent = current;

                if ((newNode->data < current->data))
                {
                    if (current->left->state == nilState) break;

                    Node* mod_left = copyNode(current->left);
                    mod_left->parent = current;

                    current->left = mod_left;
                    current = current->left;
                }
                else
                {
                    if (current->right->state == nilState) break;

                    Node* mod_right = copyNode(current->right);
                    mod_right->parent = current;

                    current->right = mod_right;
                    current = current->right;
                }
            }

            newNode->parent = parent;

            if (newNode->data < parent->data) parent->left = newNode;
            else parent->right = newNode;

            if (newNode->parent->parent == nullptr)
            {
                root = findRoot(newNode);
                versions[currentVer] = root;
                return;
            }

            root = findRoot(newNode);
            fixInsert(newNode);
            versions[currentVer] = root;
        }

        void remove(int data)
        {
            if (currentVer == 99)
            {
                std::cout << "limite de versões atingido\n";
                return;
            }

            if (root->state == nilState)
            {
                currentVer++;
                versions[currentVer] = root;
                return;
            }

            Node* nodeRem = searchHelper(root, data);
            if (nodeRem != NIL) 
            {
                Node* current = copyNode(root);
                current->parent = nullptr;

                while (current->data != data)
                {
                    if (data < current->data)
                    {
                        Node* mod_left = copyNode(current->left);
                        mod_left->parent = current;

                        current->left = mod_left;
                        current = current->left;
                    }
                    else
                    {
                        Node* mod_right = copyNode(current->right);
                        mod_right->parent = current;

                        current->right = mod_right;
                        current = current->right;
                    }
                }

                root = findRoot(current);
                deleteNode(current);
            }

            currentVer++;
            versions[currentVer] = root;
        }

        void findSuccessor(std::ostream& out, int x, int rbtVersion)
        {
            Node* current;
            int searchVer = rbtVersion;
            if (rbtVersion > currentVer) searchVer = currentVer;

            current = versions[searchVer];
            Node* successor = nullptr;

            while (current->state != nilState)
            {

                if ((current->data > x))
                {
                    successor = current;
                    if ((current->state == leftModified) && (current->timestamp > searchVer)) current = NIL;
                    else current = current->left;
                }
                else
                {
                    if ((current->state == rightModified)  && (current->timestamp > searchVer)) current = NIL;
                    else current = current->right;
                }
            }
            
            out << ((successor != nullptr) ? std::to_string(successor->data) : "+inf") << "\n";
        }

        void printTreeWithDepthAndColor(std::ostream& out, int rbtVersion)
        {
            Node* current;

            if (rbtVersion > currentVer) current = versions[currentVer];
            else current = versions[rbtVersion];

            out << "IMP " << rbtVersion << "\n";
            if (current->state == nilState)
            {
                out << "NULL\n";
                return;
            }

            inOrderHelper(current, 0, out, rbtVersion);
            out << "\n";
        }

        Node* getRoot() { return root; }
        Node* getNIL() { return NIL; }
        void setRoot(Node* r) { root = r; }
};
