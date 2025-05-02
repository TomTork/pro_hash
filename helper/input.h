#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>

using namespace std;

static void input(string &data, const string &preview) {
    cout << preview << endl;
    cin >> data;
}

static void input(int &data, const string &preview) {
    cout << preview << endl;
    cin >> data;
}

#endif //INPUT_H
