#include <iostream>
#include <string>

struct BigNumber {
    int* digits;
    size_t size;
};

BigNumber fromString(const std::string& text) {
    BigNumber number{new int[text.size()](), text.size()};
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

BigNumber multiply(const BigNumber& a, const BigNumber& b) {
    BigNumber result{new int[a.size + b.size](), a.size + b.size};

    // Каждая пара цифр влияет на разряд i + j, перенос идёт в следующий разряд.
    for (size_t i = 0; i < a.size; ++i) {
        int carry = 0;
        for (size_t j = 0; j < b.size; ++j) {
            int current = result.digits[i + j] + a.digits[i] * b.digits[j] + carry;
            result.digits[i + j] = current % 10;
            carry = current / 10;
        }
        size_t position = i + b.size;
        while (carry > 0) {
            int current = result.digits[position] + carry;
            result.digits[position] = current % 10;
            carry = current / 10;
            ++position;
        }
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
    BigNumber product = multiply(a, b);

    std::cout << "Произведение: ";
    print(product);
    std::cout << '\n';

    delete[] a.digits;
    delete[] b.digits;
    delete[] product.digits;
    return 0;
}
