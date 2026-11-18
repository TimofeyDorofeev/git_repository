#include <iostream>
#include <utility>

void gnomeSort(int* values, size_t size) {
    size_t i = 1;
    // Единственный цикл: движение вперёд при верном порядке и назад после обмена.
    while (i < size) {
        if (i == 0 || values[i - 1] <= values[i]) {
            ++i;
        } else {
            std::swap(values[i - 1], values[i]);
            --i;
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
    gnomeSort(values, size);

    std::cout << "Отсортированный массив:\n";
    for (size_t i = 0; i < size; ++i) std::cout << values[i] << ' ';
    std::cout << '\n';
    delete[] values;
    return 0;
}
