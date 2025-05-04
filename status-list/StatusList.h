//
// Created by Дмитрий Саиткулов on 30.04.2025.
//

#ifndef STATUSLIST_H
#define STATUSLIST_H

#include "../types/Status.h"

struct Node {
    Status data;
    Node* prev;
    Node* next;

    explicit Node(const Status& status);
};

class StatusList {
public:
    StatusList();
    ~StatusList();

    void push_back(const Status& status);
    void insertionSort();
    void print() const;
    bool remove(const string& number);
    [[nodiscard]] vector<Status*> get(const string& number) const;
    [[nodiscard]] vector<Status*> getByPassport(const string& passport) const;

private:
    Node* head;
    Node* tail;
};

#endif //STATUSLIST_H
