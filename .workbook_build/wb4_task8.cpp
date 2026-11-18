#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstring>

void insertionSort(int* a, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        int value = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > value) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = value;
    }
}

void binaryInsertionSort(int* a, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        int value = a[i];
        size_t left = 0, right = i;

        // В уже отсортированной части ищем первую позицию, большую value.
        while (left < right) {
            size_t middle = left + (right - left) / 2;
            if (a[middle] <= value) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        // Бинарный поиск сокращает сравнения, а memmove быстро сдвигает блок памяти.
        if (left < i) {
            std::memmove(a + left + 1, a + left, (i - left) * sizeof(int));
            a[left] = value;
        }
    }
}

bool isSorted(const int* a, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        if (a[i - 1] > a[i]) return false;
    }
    return true;
}

int main() {
    size_t size, repetitions;
    std::cout << "Размер массива и число повторений: ";
    std::cin >> size >> repetitions;
    if (size == 0 || repetitions == 0) return 1;

    int* original = new int[size];
    int* working = new int[size];
    std::mt19937 generator(12345);
    std::uniform_int_distribution<int> distribution(-1000000, 1000000);
    for (size_t i = 0; i < size; ++i) original[i] = distribution(generator);

    std::chrono::nanoseconds simpleTime(0), binaryTime(0);
    for (size_t i = 0; i < repetitions; ++i) {
        std::copy(original, original + size, working);
        auto start = std::chrono::steady_clock::now();
        insertionSort(working, size);
        auto finish = std::chrono::steady_clock::now();
        simpleTime += finish - start;
    }
    bool simpleCorrect = isSorted(working, size);

    for (size_t i = 0; i < repetitions; ++i) {
        std::copy(original, original + size, working);
        auto start = std::chrono::steady_clock::now();
        binaryInsertionSort(working, size);
        auto finish = std::chrono::steady_clock::now();
        binaryTime += finish - start;
    }
    bool binaryCorrect = isSorted(working, size);

    std::cout << "Обычные вставки: "
              << std::chrono::duration<double, std::milli>(simpleTime).count()
              << " мс; порядок " << (simpleCorrect ? "верный" : "неверный") << '\n';
    std::cout << "Вставки с половинным делением: "
              << std::chrono::duration<double, std::milli>(binaryTime).count()
              << " мс; порядок " << (binaryCorrect ? "верный" : "неверный") << '\n';
    std::cout << "Число сравнений снижается до O(n log n), но сдвиги остаются O(n^2).\n";

    delete[] original;
    delete[] working;
    return 0;
}
