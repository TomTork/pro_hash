#ifndef CHECKNUMBER_H
#define CHECKNUMBER_H

#include <string>
#include <iostream>

using namespace std;

static bool checkNumber(string& number, const string& preview = "Input number in format NNN-NNNNNNN:") {
    cout << preview << endl;
    const string valid = "1234567890-";
    while (true) {
        cin >> number;
        if (number.empty()) return false;
        if (number.length() == 11 && number[3] == '-') {
            bool state = true;
            for (int i = 0; i < number.length(); i++) {
                if (!valid.contains(number[i])) {
                    state = false;
                    break;
                }
            }
            if (state) return true;
        }
        cerr << "Incorrect number: " << number << ". Try again." << endl;
    }
    return false;
}

#endif //CHECKNUMBER_H
