#include <iostream>
#include <string>
#include <algorithm>

void printDigits(const int* digits, size_t size) {
    for (size_t i = size; i-- > 0;) {
        std::cout << digits[i];
    }
}

bool isZero(const int* digits, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (digits[i] != 0) return false;
    }
    return true;
}

bool isNumber(const std::string& text) {
    if (text.empty()) return false;
    for (char c : text) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

int* toArray(const std::string& text, size_t size) {
    int* digits = new int[size]();
    for (size_t i = 0; i < text.size(); ++i) {
        digits[i] = text[text.size() - 1 - i] - '0';
    }
    return digits;
}

int main() {
    std::string first, second;
    std::cout << "Введите два десятичных числа: ";
    std::cin >> first >> second;
    if (!isNumber(first) || !isNumber(second)) {
        std::cerr << "Ошибка: введены не числа.\n";
        return 1;
    }

    size_t size = std::max(first.size(), second.size()) + 1;
    int* a = toArray(first, size);
    int* b = toArray(second, size);
    int step = 0;

    while (true) {
        int* sum = new int[size]();
        int* carry = new int[size]();

        // Отдельно сохраняем цифры суммы и десятки, требующие переноса.
        for (size_t i = 0; i < size; ++i) {
            int current = a[i] + b[i];
            sum[i] = current % 10;
            if (i + 1 < size) carry[i + 1] = current / 10;
        }

        std::cout << "\nШаг " << step++ << '\n';
        std::cout << "A:        "; printDigits(a, size);
        std::cout << "\nB:        "; printDigits(b, size);
        std::cout << "\nСумма:    "; printDigits(sum, size);
        std::cout << "\nПереносы: "; printDigits(carry, size);
        std::cout << '\n';

        delete[] a;
        delete[] b;
        if (isZero(carry, size)) {
            std::cout << "\nРезультат: ";
            printDigits(sum, size);
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
