#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib>

void bubbleSort(int* a, size_t n) {
    for (size_t end = n; end > 1; --end) {
        bool swapped = false;
        for (size_t i = 1; i < end; ++i) {
            if (a[i - 1] > a[i]) {
                std::swap(a[i - 1], a[i]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void cocktailSort(int* a, size_t n) {
    if (n < 2) return;
    size_t left = 0, right = n - 1;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (size_t i = left; i < right; ++i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        --right;
        swapped = false;
        for (size_t i = right; i > left; --i) {
            if (a[i - 1] > a[i]) {
                std::swap(a[i - 1], a[i]);
                swapped = true;
            }
        }
        ++left;
    }
}

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

void selectionSort(int* a, size_t n) {
    for (size_t i = 0; i + 1 < n; ++i) {
        size_t minimum = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (a[j] < a[minimum]) minimum = j;
        }
        if (minimum != i) std::swap(a[i], a[minimum]);
    }
}

void shellSort(int* a, size_t n) {
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; ++i) {
            int value = a[i];
            size_t j = i;
            while (j >= gap && a[j - gap] > value) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = value;
        }
    }
}

void gnomeSort(int* a, size_t n) {
    size_t i = 1;
    while (i < n) {
        if (i == 0 || a[i - 1] <= a[i]) {
            ++i;
        } else {
            std::swap(a[i - 1], a[i]);
            --i;
        }
    }
}

bool isSorted(const int* a, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        if (a[i - 1] > a[i]) return false;
    }
    return true;
}

using SortFunction = void (*)(int*, size_t);
struct SortInfo {
    const char* name;
    SortFunction function;
};

int main(int argc, char* argv[]) {
    // Аргумент командной строки позволяет сделать короткий контрольный запуск.
    const size_t largeSize = argc == 2 ? std::strtoull(argv[1], nullptr, 10) : 1000000;
    if (largeSize == 0) {
        std::cerr << "Размер большого массива должен быть положительным.\n";
        return 1;
    }
    const size_t sizes[] = {100, largeSize};
    const SortInfo sorts[] = {
        {"Пузырьковая", bubbleSort},
        {"Шейкерная", cocktailSort},
        {"Вставками", insertionSort},
        {"Выбором", selectionSort},
        {"Шелла", shellSort},
        {"Гномья", gnomeSort}
    };

    std::mt19937 generator(12345);
    std::uniform_int_distribution<int> distribution(-1000000, 1000000);
    std::cout << "Для полного задания запустите программу без аргументов: большой размер = 1000000.\n";
    std::cout << "Квадратичные алгоритмы на таком массиве могут работать очень долго.\n";

    for (size_t size : sizes) {
        int* original = new int[size];
        for (size_t i = 0; i < size; ++i) original[i] = distribution(generator);
        std::cout << "\nРазмер массива: " << size << '\n';

        for (const SortInfo& sort : sorts) {
            int* working = new int[size];
            std::copy(original, original + size, working);
            auto start = std::chrono::steady_clock::now();
            sort.function(working, size);
            auto finish = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << sort.name << ": " << elapsed.count() << " мс; порядок "
                      << (isSorted(working, size) ? "верный" : "неверный") << '\n';
            delete[] working;
        }
        delete[] original;
    }
    return 0;
}
