#include <iostream>
#include <string>

struct BigNumber {
    int* digits;
    size_t size;
};

BigNumber readNumber(const std::string& text) {
    BigNumber number{new int[text.size()], text.size()};
    for (size_t i = 0; i < text.size(); ++i) {
        number.digits[i] = text[text.size() - 1 - i] - '0';
    }
    return number;
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

bool isNumber(const std::string& text) {
    if (text.empty() || (text.size() > 1 && text[0] == '0')) {
        return false;
    }
    for (char c : text) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

int main() {
    std::string first, second;
    std::cout << "Введите два целых неотрицательных числа:\n";
    std::cin >> first >> second;

    if (!isNumber(first) || !isNumber(second) ||
        first.size() < 11 || second.size() < 11) {
        std::cerr << "Нужны два числа без ведущих нулей, каждое не короче 11 цифр.\n";
        return 1;
    }

    BigNumber a = readNumber(first);
    BigNumber b = readNumber(second);
    int result = compare(a, b);

    if (result > 0) {
        std::cout << "Первое число больше.\n";
    } else if (result < 0) {
        std::cout << "Второе число больше.\n";
    } else {
        std::cout << "Числа равны.\n";
    }

    delete[] a.digits;
    delete[] b.digits;
    return 0;
}
