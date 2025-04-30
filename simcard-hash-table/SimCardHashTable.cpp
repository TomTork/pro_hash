#include "SimCardHashTable.h"

using namespace std;

SimCardHashTable::SimCardHashTable(const size_t cap) : capacity(cap), size(0) {
    table.resize(capacity);
}

size_t SimCardHashTable::hash1(const string& key) const {
    size_t hash = 0;
    for (const char c : key) {
        if (isdigit(c)) {
            hash = hash * 31 + (c - '0');
        }
    }
    return hash % capacity;
}

size_t SimCardHashTable::hash2(const string& key) const {
    size_t hash = 0;
    for (const char c : key) {
        if (isdigit(c)) {
            hash = hash * 17 + (c - '0');
        }
    }
    return (hash % (capacity - 1)) + 1;
}

bool SimCardHashTable::insert(const SimCard& sim) {
    if (size >= capacity - 2) rehash();
    const size_t h1 = hash1(sim.number);
    const size_t h2 = hash2(sim.number);
    for (size_t i = 0; i < capacity; i++) {
        if (const size_t index = (h1 + i * h2) % capacity; !table[index].occupied || table[index].deleted) {
            table[index].sim = sim;
            table[index].occupied = true;
            table[index].deleted = false;
            size++;
            return true;
        }
    }
    return false;
}

optional<SimCard> SimCardHashTable::find(const string& number) const {
    const size_t h1 = hash1(number);
    const size_t h2 = hash2(number);
    for (size_t i = 0; i < capacity; i++) {
        const size_t index = (h1 + i * h2) % capacity;
        if (!table[index].occupied && !table[index].deleted)
            return nullopt;
        if (table[index].occupied && !table[index].deleted && table[index].sim.number == number)
            return table[index].sim;
    }
    return nullopt;
}

bool SimCardHashTable::remove(const std::string& number) {
    const size_t h1 = hash1(number);
    const size_t h2 = hash2(number);
    for (size_t i = 0; i < capacity; i++) {
        const size_t index = (h1 + i * h2) % capacity;
        if (!table[index].occupied && !table[index].deleted)
            return false;
        if (table[index].occupied && !table[index].deleted && table[index].sim.number == number) {
            table[index].deleted = true;
            table[index].occupied = false;
            size--;
            return true;
        }
    }
    return false;
}

void SimCardHashTable::display() const {
    for (size_t i = 0; i < capacity; i++) {
        if (table[i].occupied && !table[i].deleted) {
            cout << "[" << i << "] " << table[i].sim.number
                      << " | Tariff: " << table[i].sim.tariff
                      << " | Year: " << table[i].sim.year << endl;
        }
    }
}

void SimCardHashTable::rehash() {
    capacity = capacity * 2 + 1;
    const vector<Entry> old_table = table;

    table.clear();
    table.resize(capacity);
    size = 0;

    for (const auto&[sim, occupied, deleted] : old_table) {
        if (occupied && !deleted) {
            insert(sim);
        }
    }
}
