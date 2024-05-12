#include <iostream>
#include <string>
#include <cstdint>
#include "UnMap.cpp"

uint8_t pearsonHash(const std::string& str) {
    static const uint8_t table[256] = {
    98, 6, 85, 150, 36, 23, 112, 164, 135, 207, 169, 225, 57, 11, 152, 91,
    8, 96, 9, 130, 54, 125, 176, 158, 118, 252, 107, 226, 16, 220, 155, 5,
    79, 192, 94, 146, 126, 255, 140, 36, 223, 35, 208, 7, 49, 19, 138, 180,
    124, 79, 35, 221, 22, 142, 107, 204, 121, 174, 238, 103, 65, 44, 217, 18,
    137, 240, 21, 176, 170, 184, 198, 253, 27, 96, 93, 242, 68, 18, 96, 149,
    152, 123, 177, 118, 126, 19, 43, 233, 31, 205, 169, 70, 85, 40, 163, 175,
    223, 97, 26, 240, 82, 59, 219, 233, 151, 98, 3, 206, 219, 20, 250, 162,
    46, 1, 192, 62, 246, 245, 250, 40, 8, 120, 47, 187, 147, 43, 226, 205,
    230, 108, 160, 57, 145, 187, 232, 224, 30, 22, 122, 75, 55, 34, 9, 96,
    112, 27, 74, 192, 238, 132, 106, 2, 250, 55, 178, 82, 218, 216, 121, 39,
    162, 184, 134, 101, 214, 171, 3, 39, 92, 139, 55, 4, 85, 164, 231, 121,
    118, 30, 181, 115, 220, 206, 206, 57, 32, 86, 131, 148, 45, 231, 21, 197,
    20, 189, 13, 92, 40, 251, 159, 208, 60, 171, 58, 44, 107, 212, 106, 107,
    17, 241, 74, 182, 109, 47, 170, 71, 55, 154, 181, 7, 35, 192, 21, 88,
    78, 65, 76, 243, 50, 118, 194, 182, 212, 233, 58, 8, 196, 60, 100, 176,
    138, 136, 201, 5, 122, 30, 34, 176, 75, 186, 125, 79, 204, 250, 237, 157
    };

    uint8_t hash = 0;
    for (char c : str) {
        hash = table[hash ^ static_cast<uint8_t>(c)];
    }
    return hash;
}

bool compareHash(const std::string& text1, const std::string& text2) {
    UnorderedMap<std::string, uint8_t> hashTable(10);
    hashTable.insert(text1, pearsonHash(text1));
    hashTable.insert(text2, pearsonHash(text2));

    uint8_t hash1 = *hashTable.search(text1);
    uint8_t hash2 = *hashTable.search(text2);
    std::cout << "Hash of \"" << text1 << "\": " << static_cast<int>(hash1) << std::endl;
    std::cout << "Hash of \"" << text2 << "\": " << static_cast<int>(hash2) << std::endl;

    return hash1 == hash2;
}

//int main() {
//    std::string text1 = "hello";
//    std::string text2 = "world";
//
//    std::cout << "Hashes are equal: " << std::boolalpha << compareHash(text1, text2) << std::endl;
//
//    return 0;
//}