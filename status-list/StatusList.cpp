#include "StatusList.h"
#include <iostream>

using namespace std;

Node::Node(const Status& status) : data(status), prev(nullptr), next(nullptr) {}

StatusList::StatusList() : head(nullptr), tail(nullptr) {}

StatusList::~StatusList() {
    const Node* current = head;
    while (current) {
        const Node* next = current->next;
        delete current;
        current = next;
    }
}

void StatusList::push_back(const Status& status) {
    const auto newNode = new Node(status);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void StatusList::insertionSort() {
    if (!head || !head->next) return;

    Node* current = head->next;
    while (current) {
        Node* next = current->next;
        Node* sorted = current->prev;

        while (sorted && sorted->data.number > current->data.number) {
            sorted = sorted->prev;
        }

        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;

        if (current == tail) tail = current->prev;
        if (current == head) head = current->next;

        if (!sorted) {
            current->next = head;
            current->prev = nullptr;
            head->prev = current;
            head = current;
        } else {
            current->next = sorted->next;
            current->prev = sorted;
            if (sorted->next) sorted->next->prev = current;
            sorted->next = current;
            if (sorted == tail) tail = current;
        }

        current = next;
    }
}

void StatusList::print() const {
    const Node* current = head;
    while (current) {
        cout << "Number: " << current->data.number
             << ", Passport: " << current->data.passport
             << ", Start: " << current->data.dateStart
             << ", End: " << current->data.dateEnd << endl;
        current = current->next;
    }
}

bool StatusList::remove(const string& number) {
    const Node* current = head;
    while (current) {
        if (current->data.number == number) {
            if (current->prev) current->prev->next = current->next;
            else head = current->next;

            if (current->next) current->next->prev = current->prev;
            else tail = current->prev;

            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}

Status* StatusList::get(const string& number) const {
    Node* current = head;
    while (current) {
        if (current->data.number == number) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

