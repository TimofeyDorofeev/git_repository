#include <iostream>
#include <string>
#include <algorithm>

void printBits(const int* bits, size_t size) {
    for (size_t i = size; i-- > 0;) {
        std::cout << bits[i];
    }
}

bool isZero(const int* bits, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (bits[i] != 0) return false;
    }
    return true;
}

bool isBinary(const std::string& text) {
    if (text.empty()) return false;
    for (char c : text) {
        if (c != '0' && c != '1') return false;
    }
    return true;
}

int* toArray(const std::string& text, size_t size) {
    int* bits = new int[size]();
    for (size_t i = 0; i < text.size(); ++i) {
        bits[i] = text[text.size() - 1 - i] - '0';
    }
    return bits;
}

int main() {
    std::string first, second;
    std::cout << "Введите два двоичных числа: ";
    std::cin >> first >> second;
    if (!isBinary(first) || !isBinary(second)) {
        std::cerr << "Ошибка: допустимы только цифры 0 и 1.\n";
        return 1;
    }

    size_t size = std::max(first.size(), second.size()) + 1;
    int* a = toArray(first, size);
    int* b = toArray(second, size);
    int step = 0;

    while (true) {
        int* sum = new int[size]();
        int* carry = new int[size]();

        // XOR формирует сумму без переноса, AND определяет позиции переносов.
        for (size_t i = 0; i < size; ++i) {
            sum[i] = a[i] ^ b[i];
            if (i + 1 < size) carry[i + 1] = a[i] & b[i];
        }

        std::cout << "\nШаг " << step++ << '\n';
        std::cout << "A:       "; printBits(a, size);
        std::cout << "\nB:       "; printBits(b, size);
        std::cout << "\nСумма:   "; printBits(sum, size);
        std::cout << "\nПереносы: "; printBits(carry, size);
        std::cout << '\n';

        delete[] a;
        delete[] b;
        if (isZero(carry, size)) {
            std::cout << "\nРезультат: ";
            printBits(sum, size);
            std::cout << '\n';
            delete[] sum;
            delete[] carry;
            break;
        }
        a = sum;
        b = carry;
    }
    return 0;
}
