#ifndef ISNUMBER_H
#define ISNUMBER_H

#include <string>
#include <__algorithm/ranges_all_of.h>

using namespace std;

static bool isNumber(const string& str) {
    return !str.empty() && std::ranges::all_of(str, [](const char c) { return isdigit(c); });
}

#endif //ISNUMBER_H
