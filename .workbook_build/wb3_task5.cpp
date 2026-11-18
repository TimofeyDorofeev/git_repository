#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>

struct BigNumber {
    int* digits;
    size_t size;

    explicit BigNumber(size_t length = 1) : digits(new int[length]()), size(length) {}
    BigNumber(const BigNumber&) = delete;
    BigNumber& operator=(const BigNumber&) = delete;

    BigNumber(BigNumber&& other) noexcept : digits(other.digits), size(other.size) {
        other.digits = nullptr;
        other.size = 0;
    }
    BigNumber& operator=(BigNumber&& other) noexcept {
        if (this != &other) {
            delete[] digits;
            digits = other.digits;
            size = other.size;
            other.digits = nullptr;
            other.size = 0;
        }
        return *this;
    }
    ~BigNumber() { delete[] digits; }
};

void normalize(BigNumber& a) {
    while (a.size > 1 && a.digits[a.size - 1] == 0) --a.size;
}

BigNumber fromString(const std::string& text) {
    BigNumber result(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        result.digits[i] = text[text.size() - 1 - i] - '0';
    }
    normalize(result);
    return result;
}

BigNumber slice(const BigNumber& a, size_t start, size_t length) {
    if (start >= a.size) return BigNumber();
    length = std::min(length, a.size - start);
    BigNumber result(length);
    std::copy(a.digits + start, a.digits + start + length, result.digits);
    normalize(result);
    return result;
}

int compare(const BigNumber& a, const BigNumber& b) {
    if (a.size != b.size) return a.size < b.size ? -1 : 1;
    for (size_t i = a.size; i-- > 0;) {
        if (a.digits[i] != b.digits[i]) return a.digits[i] < b.digits[i] ? -1 : 1;
    }
    return 0;
}

BigNumber add(const BigNumber& a, const BigNumber& b) {
    BigNumber result(std::max(a.size, b.size) + 1);
    int carry = 0;
    for (size_t i = 0; i + 1 < result.size; ++i) {
        int sum = carry;
        if (i < a.size) sum += a.digits[i];
        if (i < b.size) sum += b.digits[i];
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }
    result.digits[result.size - 1] = carry;
    normalize(result);
    return result;
}

BigNumber subtract(const BigNumber& a, const BigNumber& b) {
    BigNumber result(a.size);
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

BigNumber shiftLeft(const BigNumber& a, size_t positions) {
    if (a.size == 1 && a.digits[0] == 0) return BigNumber();
    BigNumber result(a.size + positions);
    std::copy(a.digits, a.digits + a.size, result.digits + positions);
    return result;
}

BigNumber multiplySchool(const BigNumber& a, const BigNumber& b) {
    BigNumber result(a.size + b.size);
    for (size_t i = 0; i < a.size; ++i) {
        int carry = 0;
        for (size_t j = 0; j < b.size; ++j) {
            int value = result.digits[i + j] + a.digits[i] * b.digits[j] + carry;
            result.digits[i + j] = value % 10;
            carry = value / 10;
        }
        size_t position = i + b.size;
        while (carry > 0) {
            int value = result.digits[position] + carry;
            result.digits[position] = value % 10;
            carry = value / 10;
            ++position;
        }
    }
    normalize(result);
    return result;
}

BigNumber karatsuba(const BigNumber& a, const BigNumber& b) {
    // На коротких числах столбик быстрее из-за отсутствия рекурсивных вызовов.
    if (std::min(a.size, b.size) <= 32) return multiplySchool(a, b);

    size_t half = std::max(a.size, b.size) / 2;
    BigNumber a0 = slice(a, 0, half);
    BigNumber a1 = slice(a, half, a.size - std::min(half, a.size));
    BigNumber b0 = slice(b, 0, half);
    BigNumber b1 = slice(b, half, b.size - std::min(half, b.size));

    BigNumber z0 = karatsuba(a0, b0);
    BigNumber z2 = karatsuba(a1, b1);
    BigNumber sumA = add(a0, a1);
    BigNumber sumB = add(b0, b1);
    BigNumber z1 = karatsuba(sumA, sumB);

    // z1 = (a0+a1)(b0+b1)-z0-z2 = a0*b1+a1*b0.
    BigNumber middle = subtract(z1, z0);
    z1 = subtract(middle, z2);
    BigNumber highPart = shiftLeft(z2, 2 * half);
    BigNumber middlePart = shiftLeft(z1, half);
    BigNumber partial = add(highPart, middlePart);
    return add(partial, z0);
}

void print(const BigNumber& a) {
    for (size_t i = a.size; i-- > 0;) std::cout << a.digits[i];
}

bool equal(const BigNumber& a, const BigNumber& b) {
    return compare(a, b) == 0;
}

bool isNumber(const std::string& text) {
    if (text.empty()) return false;
    for (char c : text) if (c < '0' || c > '9') return false;
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

    auto start = std::chrono::steady_clock::now();
    BigNumber school = multiplySchool(a, b);
    auto finish = std::chrono::steady_clock::now();
    auto schoolTime = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);

    start = std::chrono::steady_clock::now();
    BigNumber fast = karatsuba(a, b);
    finish = std::chrono::steady_clock::now();
    auto fastTime = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);

    std::cout << "Произведение: ";
    print(school);
    std::cout << "\nСтолбик: " << schoolTime.count() << " мкс";
    std::cout << "\nКарацуба: " << fastTime.count() << " мкс";
    std::cout << "\nРезультаты совпадают: " << (equal(school, fast) ? "да" : "нет") << '\n';
    return 0;
}
