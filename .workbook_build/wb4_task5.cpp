#include <iostream>

void shellSort(int* values, size_t size) {
    // Последовательность Шелла: N/2, N/4, ..., 1.
    for (size_t gap = size / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < size; ++i) {
            int value = values[i];
            size_t j = i;
            while (j >= gap && values[j - gap] > value) {
                values[j] = values[j - gap];
                j -= gap;
            }
            values[j] = value;
        }
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
    shellSort(values, size);

    std::cout << "Отсортированный массив:\n";
    for (size_t i = 0; i < size; ++i) std::cout << values[i] << ' ';
    std::cout << '\n';
    delete[] values;
    return 0;
}
