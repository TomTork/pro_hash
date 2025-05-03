#ifndef CHECKPASSPORT_H
#define CHECKPASSPORT_H

#include <string>
#include <iostream>

using namespace std;

static bool checkPassport(string& passport, const string& preview = "Input passport in format NNNN-NNNNNNN:") {
    cout << preview << endl;
    const string valid = "1234567890-";
    while (true) {
        cin >> passport;
        if (passport.empty()) return false;
        if (passport.length() == 12 && passport[4] == '-') {
            bool state = true;
            for (int i = 0; i < passport.length(); i++) {
                if (!valid.contains(passport[i])) {
                    state = false;
                    break;
                }
            }
            if (state) return true;
        }
        cerr << "Incorrect passport: " << passport << ". Try again." << endl;
    }
    return false;
}

#endif //CHECKPASSPORT_H
