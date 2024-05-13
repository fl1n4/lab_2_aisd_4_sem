#include <iostream>
#include "UnMap.cpp"

int main() {
    // Создание объекта хэш-таблицы
    UnorderedMap<int, std::string> map(3);
    UnorderedMap<int, std::string> map1(30,20);
    std::cout << "Contents of map:" << std::endl;
    map1.print();
    std::cout << std::endl;

    // Вставка элементов
    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");
    map.insert(4, "Four");
    map.insert(4, "Chetire");
    map.insert(4, "Chetire1");
    map.insert(5, "Five");
    map.insert_or_assign(5, "Six");
    //// Вывод содержимого
    std::cout << "Contents of map:" << std::endl;
    map.print();
    std::cout << std::endl;

    // Поиск и вывод элемента
    int key_to_find = 3;
    std::string* result = map.search(key_to_find);
    if (result != nullptr) {
        std::cout << "Element with key " << key_to_find << ": " << *result << std::endl;
    }
    else {
        std::cout << "Element with key " << key_to_find << " not found" << std::endl;
    }

    // Проверка наличия элемента
    int key_to_check = 5;
    if (map.contains(key_to_check)) {
        std::cout << "Element with key " << key_to_check << " exists in map" << std::endl;
    }
    else {
        std::cout << "Element with key " << key_to_check << " does not exist in map" << std::endl;
    }

    // Удаление элемента
    int key_to_erase = 2;
    if (map.erase(key_to_erase)) {
        std::cout << "Element with key " << key_to_erase << " successfully erased" << std::endl;
    }
    else {
        std::cout << "Failed to erase element with key " << key_to_erase << std::endl;
    }

    // Вывод содержимого после удаления
    std::cout << "\nContents of map after erasing:" << std::endl;
    map.print();

    // Проверка количества элементов с одинаковым ключом
    std::cout << "Count of key 4: " << map.count(4) << std::endl;

    return 0;
}