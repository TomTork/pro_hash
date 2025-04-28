#ifndef READLINESFROMFILE_H
#define READLINESFROMFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

inline vector<string> readLinesFromFile(const string& filePath) {
    vector<string> lines;
    ifstream file(filePath);
    if (!file.is_open()) throw runtime_error("Could not open file " + filePath);
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

#endif //READLINESFROMFILE_H
