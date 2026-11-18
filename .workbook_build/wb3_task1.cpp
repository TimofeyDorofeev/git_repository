#include <iostream>
#include <string>
#include <algorithm>

struct BigNumber {
    int* digits;
    size_t size;
};

BigNumber fromString(const std::string& text) {
    BigNumber number{new int[text.size()], text.size()};
    for (size_t i = 0; i < text.size(); ++i) {
        number.digits[i] = text[text.size() - 1 - i] - '0';
    }
    return number;
}

void normalize(BigNumber& number) {
    while (number.size > 1 && number.digits[number.size - 1] == 0) {
        --number.size;
    }
}

int compare(const BigNumber& a, const BigNumber& b) {
    if (a.size != b.size) {
        return a.size < b.size ? -1 : 1;
    }
    for (size_t i = a.size; i-- > 0;) {
        if (a.digits[i] != b.digits[i]) {
            return a.digits[i] < b.digits[i] ? -1 : 1;
        }
    }
    return 0;
}

BigNumber add(const BigNumber& a, const BigNumber& b) {
    size_t size = std::max(a.size, b.size) + 1;
    BigNumber result{new int[size](), size};
    int carry = 0;

    for (size_t i = 0; i + 1 < size; ++i) {
        int sum = carry;
        if (i < a.size) sum += a.digits[i];
        if (i < b.size) sum += b.digits[i];
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }
    result.digits[size - 1] = carry;
    normalize(result);
    return result;
}

// Функция вызывается только при a >= b.
BigNumber subtract(const BigNumber& a, const BigNumber& b) {
    BigNumber result{new int[a.size](), a.size};
    int borrow = 0;

    for (size_t i = 0; i < a.size; ++i) {
        int difference = a.digits[i] - borrow;
        if (i < b.size) difference -= b.digits[i];
        if (difference < 0) {
            difference += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = difference;
    }
    normalize(result);
    return result;
}

void print(const BigNumber& number) {
    for (size_t i = number.size; i-- > 0;) {
        std::cout << number.digits[i];
    }
}

bool isNumber(const std::string& text) {
    if (text.empty()) return false;
    for (char c : text) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

int main() {
    std::string first, second;
    std::cout << "Введите два целых неотрицательных числа:\n";
    std::cin >> first >> second;
    if (!isNumber(first) || !isNumber(second)) {
        std::cerr << "Ошибка: введены не числа.\n";
        return 1;
    }

    BigNumber a = fromString(first);
    BigNumber b = fromString(second);
    normalize(a);
    normalize(b);

    BigNumber sum = add(a, b);
    int relation = compare(a, b);
    BigNumber difference = relation >= 0 ? subtract(a, b) : subtract(b, a);

    std::cout << "Сумма: ";
    print(sum);
    std::cout << "\nРазность: ";
    if (relation < 0 && !(difference.size == 1 && difference.digits[0] == 0)) {
        std::cout << '-';
    }
    print(difference);
    std::cout << '\n';

    delete[] a.digits;
    delete[] b.digits;
    delete[] sum.digits;
    delete[] difference.digits;
    return 0;
}
