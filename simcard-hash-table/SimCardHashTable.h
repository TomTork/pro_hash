#ifndef SIMCARDHASHTABLE_H
#define SIMCARDHASHTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include "../types/SimCard.h"
#include <optional>

using namespace std;

class SimCardHashTable {
public:
    explicit SimCardHashTable(size_t cap = 101);

    bool insert(const SimCard& sim);
    [[nodiscard]] optional<SimCard> find(const string& number) const;
    bool remove(const std::string& number);
    void display() const;
    void displayByTariff(const string& tariff) const;
    bool updateExists(const string& number, const bool& exists);
    [[nodiscard]] vector<SimCard> getAll() const;

private:
    struct Entry {
        SimCard sim;
        bool occupied = false;
        bool deleted = false;
    };

    vector<Entry> table;
    size_t capacity;
    size_t size;

    [[nodiscard]] size_t hash1(const std::string& key) const;
    [[nodiscard]] size_t hash2(const std::string& key) const;

    void rehash();
};

#endif //SIMCARDHASHTABLE_H
