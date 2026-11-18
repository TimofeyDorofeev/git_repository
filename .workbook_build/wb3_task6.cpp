#include <iostream>
#include <string>
#include <algorithm>

struct BigNumber {
    int* digits;
    size_t size;
};

BigNumber zero() {
    return BigNumber{new int[1](), 1};
}

BigNumber fromString(const std::string& text) {
    BigNumber number{new int[text.size()](), text.size()};
    for (size_t i = 0; i < text.size(); ++i) {
        number.digits[i] = text[text.size() - 1 - i] - '0';
    }
    return number;
}

void normalize(BigNumber& a) {
    while (a.size > 1 && a.digits[a.size - 1] == 0) --a.size;
}

int compare(const BigNumber& a, const BigNumber& b) {
    if (a.size != b.size) return a.size < b.size ? -1 : 1;
    for (size_t i = a.size; i-- > 0;) {
        if (a.digits[i] != b.digits[i]) return a.digits[i] < b.digits[i] ? -1 : 1;
    }
    return 0;
}

BigNumber subtract(const BigNumber& a, const BigNumber& b) {
    BigNumber result{new int[a.size](), a.size};
    int borrow = 0;
    for (size_t i = 0; i < a.size; ++i) {
        int value = a.digits[i] - borrow - (i < b.size ? b.digits[i] : 0);
        if (value < 0) {
            value += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = value;
    }
    normalize(result);
    return result;
}

BigNumber multiplyByDigit(const BigNumber& a, int digit) {
    BigNumber result{new int[a.size + 1](), a.size + 1};
    int carry = 0;
    for (size_t i = 0; i < a.size; ++i) {
        int value = a.digits[i] * digit + carry;
        result.digits[i] = value % 10;
        carry = value / 10;
    }
    result.digits[a.size] = carry;
    normalize(result);
    return result;
}

BigNumber appendDigit(const BigNumber& a, int digit) {
    BigNumber result{new int[a.size + 1](), a.size + 1};
    result.digits[0] = digit;
    std::copy(a.digits, a.digits + a.size, result.digits + 1);
    normalize(result);
    return result;
}

void print(const BigNumber& a) {
    for (size_t i = a.size; i-- > 0;) std::cout << a.digits[i];
}

bool isNumber(const std::string& text) {
    if (text.empty()) return false;
    for (char c : text) if (c < '0' || c > '9') return false;
    return true;
}

int main() {
    std::string first, second;
    std::cout << "Введите делимое и делитель: ";
    std::cin >> first >> second;
    if (!isNumber(first) || !isNumber(second) ||
        (second.size() == 1 && second[0] == '0')) {
        std::cerr << "Ошибка: нужны неотрицательные числа, делитель не равен нулю.\n";
        return 1;
    }

    BigNumber a = fromString(first);
    BigNumber b = fromString(second);
    normalize(a);
    normalize(b);
    BigNumber quotient{new int[a.size](), a.size};
    BigNumber remainder = zero();

    for (size_t i = a.size; i-- > 0;) {
        BigNumber extended = appendDigit(remainder, a.digits[i]);
        delete[] remainder.digits;
        remainder = extended;

        // Половинное деление на [0; 9] находит максимальную подходящую цифру частного.
        int left = 0, right = 9, best = 0;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            BigNumber product = multiplyByDigit(b, middle);
            if (compare(product, remainder) <= 0) {
                best = middle;
                left = middle + 1;
            } else {
                right = middle - 1;
            }
            delete[] product.digits;
        }
        quotient.digits[i] = best;
        BigNumber product = multiplyByDigit(b, best);
        BigNumber nextRemainder = subtract(remainder, product);
        delete[] remainder.digits;
        delete[] product.digits;
        remainder = nextRemainder;
    }
    normalize(quotient);

    std::cout << "Частное: ";
    print(quotient);
    std::cout << "\nОстаток: ";
    print(remainder);
    std::cout << '\n';

    delete[] a.digits;
    delete[] b.digits;
    delete[] quotient.digits;
    delete[] remainder.digits;
    return 0;
}
