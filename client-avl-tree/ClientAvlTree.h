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

        explicit Node(const Client& client)
            : data(client), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    static int getHeight(const Node* node);
    static int getBalance(const Node* node);
    static Node* rotateRight(Node* y);
    static Node* rotateLeft(Node* x);
    static Node* insert(Node* node, const Client& client);
    void preOrder(const Node* node);
    static void clear(const Node* node);
    static Node* minValueNode(Node* node);
    Node* remove(Node* node, const string& passport);
    Client* find(Node* node, const string& passport);
    Client* findByFragment(Node* node, const string& fragment);

public:
    ClientAvlTree();
    ~ClientAvlTree();

    /**
     * @brief Добавление нового клиента
     * @param client
     */
    void insert(const Client& client);

    /**
     * @brief Вывод дерева
     */
    void preOrder();
    bool remove(const string& passport);
    Client* find(const string& passport);
    Client* findByFragment(const string& fragment);
    void clear();
};



#endif //AVLTREE_H
