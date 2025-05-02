#ifndef DIRECTSEARCH_H
#define DIRECTSEARCH_H

#include <string>

using namespace std;

static bool directSearch(const string& text, const string& pattern) {
    const unsigned long n = text.length();
    const unsigned long m = pattern.length();
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) break;
        }
        if (j == m) return true;
    }
    return false;
}

#endif //DIRECTSEARCH_H
