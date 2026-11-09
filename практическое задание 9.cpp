// Дорофеев Тимофей Сергеевич ЭФБО-08-26

// задание 1
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Строка с запрещёнными буквами (в нижнем регистре)
    const string forbidden = "useragmnt";

    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    if (!inFile.is_open()) {
        cerr << "Ошибка: не удалось открыть input.txt\n";
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось создать output.txt\n";
        return 1;
    }

    char ch;
    while (inFile.get(ch)) {
        char lower = ch;
        // Приводим к нижнему регистру, если это заглавная буква
        if (ch >= 'A' && ch <= 'Z') {
            lower = ch + ('a' - 'A');
        }

        bool shouldRemove = false;
        // Проверяем, есть ли символ в строке forbidden
        for (size_t i = 0; i < forbidden.size(); ++i) {
            if (lower == forbidden[i]) {
                shouldRemove = true;
                break;
            }
        }

        // Если символ НЕ запрещён, записываем его
        if (!shouldRemove) {
            outFile.put(ch);
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}


// задание 2
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream fileX("input1.txt");
    ifstream fileY("input2.txt");

    if (!fileX.is_open() || !fileY.is_open()) {
        cerr << "Ошибка: не удалось открыть файлы input1.txt или input2.txt\n";
        return 1;
    }

    string X, Y;
    fileX >> X;
    fileY >> Y;

    fileX.close();
    fileY.close();

    size_t pos = X.find(Y);

    ofstream out("output.txt");
    if (pos != string::npos) {
        out << "yes\n";
    } else {
        out << "no\n";
    }
    out.close();

    return 0;
}


// задание 3
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Функция переводит строку с числом в двоичную строку
string toBinary(const string& numStr) {
    long long value = 0;

    // Превращаем строку цифр в число вручную
    for (char c : numStr) {
        // Проверяем, что символ — цифра, без <cctype>
        if (c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
        }
        // Если вдруг попадётся не цифра — по условию не должно быть, но так безопаснее
    }

    if (value == 0) {
        return "0";
    }

    string binary;
    while (value > 0) {
        if (value % 2 == 0) {
            binary.push_back('0');
        } else {
            binary.push_back('1');
        }
        value /= 2;
    }

    // Разворачиваем строку: биты записаны в обратном порядке
    for (size_t i = 0, j = binary.size() - 1; i < j; ++i, --j) {
        char tmp = binary[i];
        binary[i] = binary[j];
        binary[j] = tmp;
    }
    return binary;
}

int main() {
    ifstream inFile("input_for_nuber3.txt");
    ofstream outFile("output.txt");

    // Проверка открытия файлов
    if (!inFile.is_open()) {
        cerr << "Ошибка: не удалось открыть input.txt\n";
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось создать output.txt\n";
        return 1;
    }

    string line;
    getline(inFile, line);

    size_t i = 0;
    while (i < line.size()) {
        // Ручная проверка: символ — цифра? (без <cctype>)
        if (line[i] >= '0' && line[i] <= '9') {
            size_t start = i;
            // Собираем всё число подряд
            while (i < line.size() && (line[i] >= '0' && line[i] <= '9')) {
                ++i;
            }
            string numStr = line.substr(start, i - start);
            string binStr = toBinary(numStr);
            outFile << binStr;
        } else {
            // Не цифра — просто копируем символ
            outFile.put(line[i]);
            ++i;
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}

