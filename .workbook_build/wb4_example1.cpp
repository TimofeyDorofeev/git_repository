#include <iostream>
#include <chrono>
#include <utility>

void mySwap(int& a, int& b) {
    int temporary = a;
    a = b;
    b = temporary;
}

int main() {
    size_t size, first, second, repetitions;
    std::cout << "Размер массива, два индекса и число повторений: ";
    std::cin >> size >> first >> second >> repetitions;
    if (size < 2 || first >= size || second >= size) {
        std::cerr << "Ошибка в исходных данных.\n";
        return 1;
    }

    int* values = new int[size];
    std::cout << "Введите элементы массива:\n";
    for (size_t i = 0; i < size; ++i) std::cin >> values[i];

    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < repetitions; ++i) {
        std::swap(values[first], values[second]);
    }
    auto finish = std::chrono::steady_clock::now();
    auto standardTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < repetitions; ++i) {
        mySwap(values[first], values[second]);
    }
    finish = std::chrono::steady_clock::now();
    auto customTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    std::cout << "std::swap: " << standardTime.count() << " нс\n";
    std::cout << "Собственная функция: " << customTime.count() << " нс\n";
    std::cout << "Контрольная сумма: ";
    long long sum = 0;
    for (size_t i = 0; i < size; ++i) sum += values[i];
    std::cout << sum << '\n';

    delete[] values;
    return 0;
}
