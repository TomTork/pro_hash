#include <iostream>
#include "ClientAvlTree.h"

using namespace std;

ClientAvlTree::ClientAvlTree() : root(nullptr) {}

ClientAvlTree::~ClientAvlTree() {
    clear(root);
}

void ClientAvlTree::clear(const Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int ClientAvlTree::getHeight(const Node* node) {
    return node ? node->height : 0;
}

int ClientAvlTree::getBalance(const Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

ClientAvlTree::Node* ClientAvlTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Поворот
    x->right = y;
    y->left = T2;

    // Обновляем высоты
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

ClientAvlTree::Node* ClientAvlTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Поворот
    y->left = x;
    x->right = T2;

    // Обновляем высоты
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

ClientAvlTree::Node* ClientAvlTree::insert(Node* node, const Client& client) {
    if (!node)
        return new Node(client);

    if (client.passport < node->data.passport)
        node->left = insert(node->left, client);
    else if (client.passport > node->data.passport)
        node->right = insert(node->right, client);
    else
        return node; // Дубликаты не вставляются

    // Обновляем высоту
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    const int balance = getBalance(node);

    // Балансировка
    // Left Left Case
    if (balance > 1 && client.passport < node->left->data.passport)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && client.passport > node->right->data.passport)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && client.passport > node->left->data.passport) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && client.passport < node->right->data.passport) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void ClientAvlTree::insert(const Client& client) {
    root = insert(root, client);
}

void ClientAvlTree::preOrder(const Node* node) {
    if (node) {
        cout << "Паспорт: " << node->data.passport << ", ФИО: " << node->data.fio << endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

void ClientAvlTree::preOrder() {
    preOrder(root);
}
