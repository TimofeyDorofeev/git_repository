#include <iostream>

void insertionSort(int* values, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        int value = values[i];
        size_t j = i;
        while (j > 0 && values[j - 1] > value) {
            values[j] = values[j - 1];
            --j;
        }
        values[j] = value;
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
    insertionSort(values, size);

    std::cout << "Отсортированный массив:\n";
    for (size_t i = 0; i < size; ++i) std::cout << values[i] << ' ';
    std::cout << '\n';
    delete[] values;
    return 0;
}
