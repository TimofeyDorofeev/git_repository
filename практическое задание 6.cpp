// задание 1

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            // Определяем значение для текущей ячейки
            if(i + j < n - 1) {
                cout << "0";
            } else if(i + j == n - 1) {
                cout << "1";
            } else {
                cout << "2";
            }
            
            // Выводим пробел между числами
            if(j < n - 1) {
                cout << " ";
            }
        }
        // Переход на новую строку
        cout << endl;
    }
    
    return 0;
}


// задание 2

#include <iostream>
using namespace std;

int main() {
    int n, m, w;
    cin >> n >> m >> w;  
    
    // Создаем карту
    char map[33][33] = {0};
    
    // Отмечаем грибы
    for(int i = 0; i < w; i++) {
        int x, y;
        cin >> x >> y;
        map[x][y] = '*';
    }
    
    // Считаем грибы вокруг
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(map[i][j] != '*') {  // Если не гриб
                int count = 0;
                // Проверяем соседей
                if(map[i-1][j-1] == '*') count++;  // верх-лево
                if(map[i-1][j] == '*') count++;    // верх
                if(map[i-1][j+1] == '*') count++;  // верх-право
                if(map[i][j-1] == '*') count++;    // лево
                if(map[i][j+1] == '*') count++;    // право
                if(map[i+1][j-1] == '*') count++;  // низ-лево
                if(map[i+1][j] == '*') count++;    // низ
                if(map[i+1][j+1] == '*') count++;  // низ-право
                
                map[i][j] = '0' + count;  // Сохраняем число
            }
        }
    }
    
    // Выводим результат
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
    
    return 0;
}


// задание 3.1

#include <iostream>
#include <string>
using namespace std;

// Функция для получения следующего элемента
string next_element(const string& s) {
    string result;
    int count = 1;
    char current = s[0];
    
    for(int i = 1; i < s.size(); i++) {
        if(s[i] == current) {
            count++;
        } else {
            result += to_string(count) + current;
            current = s[i];
            count = 1;
        }
    }
    result += to_string(count) + current;
    return result;
}

int main() {
    int x, n;
    cin >> x >> n;
    
    string current = to_string(x);
    
    for(int i = 1; i < n; i++) {
        current = next_element(current);
    }
    
    cout << current << endl;
    return 0;
}

// задание 3.2

#include <iostream>
#include <string>
using namespace std;

// Рекурсивная функция для получения n-го элемента
string get_nth_element(string s, int n) {
    if(n == 1) return s;  // Базовый случай
    
    // Функция для получения следующего элемента
    string next_element(const string& str) {
        string result;
        int count = 1;
        char current = str[0];
        
        for(int i = 1; i < str.size(); i++) {
            if(str[i] == current) {
                count++;
            } else {
                result += to_string(count) + current;
                current = str[i];
                count = 1;
            }
        }
        result += to_string(count) + current;
        return result;
    }
    
    return get_nth_element(next_element(s), n-1);
}

int main() {
    int x, n;
    cin >> x >> n;
    
    cout << get_nth_element(to_string(x), n) << endl;
    return 0;
}
