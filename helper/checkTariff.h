#ifndef CHECKTARIFF_H
#define CHECKTARIFF_H

#include <string>
#include <iostream>

using namespace std;

static bool checkTariff(string& tariff, const string& preview = "Input tariff (pro / standard / lite):") {
    cout << preview << endl;
    const string valid = "1234567890-";
    while (true) {
        cin >> tariff;
        if (tariff.empty()) return false;
        if (tariff == "pro" || tariff == "standard" || tariff == "lite") return true;
        cerr << "Incorrect tariff: " << tariff << ". Try again." << endl;
    }
    return false;
}

#endif //CHECKTARIFF_H
