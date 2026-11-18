#include <iostream>
#include <utility>

void selectionSort(int* values, size_t size) {
    for (size_t i = 0; i + 1 < size; ++i) {
        size_t minimum = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (values[j] < values[minimum]) minimum = j;
        }
        if (minimum != i) std::swap(values[i], values[minimum]);
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
    selectionSort(values, size);

    std::cout << "Отсортированный массив:\n";
    for (size_t i = 0; i < size; ++i) std::cout << values[i] << ' ';
    std::cout << '\n';
    delete[] values;
    return 0;
}
