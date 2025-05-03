#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>
#include "isNumber.h"

using namespace std;

static void input(string &data, const string &preview) {
    cout << preview << endl;
    cin >> data;
}

static void input(int &result, const string &preview) {
    string data;
    cout << preview << endl;
    while (true) {
        cin >> data;
        if (isNumber(data)) {
            result = stoi(data);
            break;
        }
        cerr << "The entered data is not a number" << endl;
    }
}

static void input(bool &result, const string &preview) {
    string data;
    cout << preview << endl;
    while (true) {
        cin >> data;
        if (data == "1" || data == "0") {
            result = static_cast<bool>(data[0] - '0');
            break;
        }
        cerr << "The entered data is not a boolean" << endl;
    }
}

#endif //INPUT_H
