#include <iostream>
#include <random>

int main() {
    size_t size;
    std::cout << "Количество цифр: ";
    std::cin >> size;

    if (size < 11) {
        std::cerr << "Для длинного числа нужно не менее 11 цифр.\n";
        return 1;
    }

    int* digits = new int[size];
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> digit(0, 9);
    std::uniform_int_distribution<int> firstDigit(1, 9);

    // Младший разряд хранится в нулевом элементе массива.
    for (size_t i = 0; i + 1 < size; ++i) {
        digits[i] = digit(generator);
    }
    digits[size - 1] = firstDigit(generator);

    std::cout << "Случайное число: ";
    for (size_t i = size; i-- > 0;) {
        std::cout << digits[i];
    }
    std::cout << '\n';

    delete[] digits;
    return 0;
}
