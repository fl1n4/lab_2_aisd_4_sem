﻿#include <iostream>
#include <vector>
#include <cstdlib>

template<typename K, typename T>
class UnorderedMap {
private:
    struct KeyValuePair {
        K key;
        T value;
        bool occupied;
        KeyValuePair() : key(), value(), occupied(false) {}
    };

    std::vector<KeyValuePair> table;
    size_t size;

    size_t hashFunction(const K& key) const {
        const size_t multiplier = 2654435761; // Простое число близкое к 2^32/φ, где φ - золотое сечение
        size_t hashValue = std::hash<K>{}(key);
        return (multiplier * hashValue) % table.size(); // Используем операцию деления
    }

    size_t findNextFreeSlot(size_t index) const {
        while (table[index].occupied) {
            index = (index + 1) % table.size();
        }
        return index;
    }

public:
    UnorderedMap(size_t initialSize) : table(initialSize), size(0) {}

    UnorderedMap(size_t initialSize, size_t elements) : UnorderedMap(initialSize) {
        for (size_t i = 0; i < elements; ++i) {
            insert(rand(), rand());
        }
    }

    UnorderedMap(const UnorderedMap& other) : table(other.table), size(other.size) {}

    ~UnorderedMap() {}

    UnorderedMap& operator=(const UnorderedMap& other) {
        if (this != &other) {
            table = other.table;
            size = other.size;
        }
        return *this;
    }

    void print() const {
        std::cout << "Table size: " << table.size() << std::endl;
        for (size_t i = 0; i < table.size(); ++i) {
            const auto& pair = table[i];
            std::cout << "Index: " << i << ", ";
            if (pair.occupied) {
                std::cout << "Key: " << pair.key << ", Value: " << pair.value << std::endl;
            }
            else {
                std::cout << "Empty" << std::endl;
            }
        }
    }

    void insert(const K& key, const T& value) {
        if (size == table.size()) {
            table.resize(table.size() * 2);
        }

        size_t index = hashFunction(key) & (table.size() - 1); // Применяем маску
        if (table[index].occupied) {
            index = findNextFreeSlot(index);
        }

        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
        ++size;
    }

    void insert_or_assign(const K& key, const T& value) {
        size_t index = hashFunction(key);
        while (table[index].occupied && table[index].key != key) {
            index = (index + 1) % table.size();
        }
        if (!table[index].occupied) {
            ++size;
        }
        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
    }

    bool contains(const K& key) const {
        size_t index = hashFunction(key);
        while (table[index].occupied) {
            if (table[index].key == key) {
                return true;
            }
            index = (index + 1) % table.size();
        }
        return false;
    }

    T* search(const K& key) {
        size_t index = hashFunction(key) & (table.size() - 1); // Применяем маску
        while (table[index].occupied) {
            if (table[index].key == key) {
                return &table[index].value;
            }
            index = (index + 1) % table.size();
        }
        return nullptr;
    }

    bool erase(const K& key) {
        size_t index = hashFunction(key);
        while (table[index].occupied) {
            if (table[index].key == key) {
                table[index].occupied = false;
                --size;
                return true;
            }
            index = (index + 1) % table.size();
        }
        return false;
    }

    int count(const K& key) const {
        size_t index = hashFunction(key);
        int count = 0;
        while (table[index].occupied) {
            if (table[index].key == key) {
                ++count;
            }
            index = (index + 1) % table.size();
        }
        return count;
    }
};