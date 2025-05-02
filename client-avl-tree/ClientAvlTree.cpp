#include <iostream>
#include "ClientAvlTree.h"

#include "../helper/directSearch.h"

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

void ClientAvlTree::clear() {
    clear(root);
    root = nullptr;
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
        cout << "Passport: " << node->data.passport << ", FIO: " << node->data.fio << endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

ClientAvlTree::Node* ClientAvlTree::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

ClientAvlTree::Node* ClientAvlTree::remove(Node* node, const string& passport) {
    if (!node) return nullptr;

    if (passport < node->data.passport)
        node->left = remove(node->left, passport);
    else if (passport > node->data.passport)
        node->right = remove(node->right, passport);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        } else {
            const Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data.passport);
        }
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    const int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

bool ClientAvlTree::remove(const string& passport) {
    if (!find(passport)) return false;
    root = remove(root, passport);
    return true;
}

Client* ClientAvlTree::find(Node* node, const string& passport) {
    if (!node) return nullptr;
    if (passport == node->data.passport)
        return &node->data;
    if (passport < node->data.passport)
        return find(node->left, passport);
    return find(node->right, passport);
}

Client* ClientAvlTree::find(const string& passport) {
    return find(root, passport);
}

Client* ClientAvlTree::findByFragment(Node* node, const string& fragment) {
    if (!node) return nullptr;
    if (directSearch(node->data.fio, fragment) || directSearch(node->data.address, fragment)) return &node->data;
    findByFragment(node->left, fragment);
    findByFragment(node->right, fragment);
}

Client* ClientAvlTree::findByFragment(const string& fragment) {
    return find(root, fragment);
}

void ClientAvlTree::preOrder() {
    preOrder(root);
}
