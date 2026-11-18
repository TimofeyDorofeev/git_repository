#include <iostream>
#include <utility>

void cocktailSort(int* values, size_t size) {
    if (size < 2) return;
    size_t left = 0, right = size - 1;
    bool swapped = true;

    while (swapped) {
        swapped = false;
        for (size_t i = left; i < right; ++i) {
            if (values[i] > values[i + 1]) {
                std::swap(values[i], values[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        --right;

        swapped = false;
        for (size_t i = right; i > left; --i) {
            if (values[i - 1] > values[i]) {
                std::swap(values[i - 1], values[i]);
                swapped = true;
            }
        }
        ++left;
    }
}

int main() {
    size_t size;
    std::cout << "Размер массива: ";
    std::cin >> size;
    if (size == 0) return 1;

    int* values = new int[size];
    std::cout << "Введите элементы:\n";
    for (size_t i = 0; i < size; ++i) std::cin >> values[i];
    cocktailSort(values, size);

    std::cout << "Отсортированный массив:\n";
    for (size_t i = 0; i < size; ++i) std::cout << values[i] << ' ';
    std::cout << '\n';
    delete[] values;
    return 0;
}
