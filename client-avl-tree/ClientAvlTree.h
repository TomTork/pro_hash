#ifndef AVLTREE_H
#define AVLTREE_H

#include "../types/Client.h"
using namespace std;

class ClientAvlTree {
private:
    struct Node {
        Client data;
        Node* left;
        Node* right;
        int height;

        Node(const Client& client)
            : data(client), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(const Node* node);
    int getBalance(const Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* insert(Node* node, const Client& client);
    void preOrder(const Node* node);
    static void clear(const Node* node);

public:
    ClientAvlTree();
    ~ClientAvlTree();

    void insert(const Client& client);
    void preOrder();
};



#endif //AVLTREE_H
