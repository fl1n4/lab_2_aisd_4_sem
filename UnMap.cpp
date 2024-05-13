#include <iostream>
#include <vector>
#include <random>
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
        const size_t multiplier = 2654435769; // Простое число близкое к 2^32/φ, где φ - золотое сечение
        //size_t hashValue = std::hash<K>{}(key);
        return (multiplier * key) % table.size(); // Используем операцию деления
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
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 1000);
        for (size_t i = 0; i < elements; ++i) {
            insert(dis(gen), dis(gen));
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

        size_t index = hashFunction(key) & (table.size() - 1);
        if (table[index].occupied) {
            index = findNextFreeSlot(index);
        }

        table[index].key = key;
        table[index].value = value;
        table[index].occupied = true;
        ++size;
    }

    void insert_or_assign(const K& key, const T& value) {
        size_t index = hashFunction(key) & (table.size() - 1);
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
        size_t index = hashFunction(key) & (table.size() - 1);
        while (table[index].occupied) {
            if (table[index].key == key) {
                return true;
            }
            index = (index + 1) % table.size();
        }
        return false;
    }

    T* search(const K& key) {
        size_t index = hashFunction(key) & (table.size() - 1);
        int pass = 0;
        while (pass < table.size())
        {
            if (table[index].key == key) {
                return &table[index].value;
            }
            pass+=1;
            index = (index + 1) % table.size();
        }
        return nullptr; // Элемент не найден
    }

    bool erase(const K& key) {
        size_t index = hashFunction(key) & (table.size() - 1);
        int pass = 0;
        while (pass < table.size())
        {
            if (table[index].key == key) {
                table[index].occupied = false;
                --size;
                return true; // Элемент удален
            }
            pass += 1;
            index = (index + 1) % table.size();
        }
        return false; // Элемент не найден
    }

    int count(const K& key) const {
        size_t index = hashFunction(key) & (table.size() - 1);
        int count = 0;
        size_t originalIndex = index;

        do {
            if (table[index].key == key) {
                ++count;
            }
            index = (index + 1) % table.size();
        } while (index != originalIndex);

        return count;
    }
};