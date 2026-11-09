// Дорофеев Тимофей Сергеевич ЭФБО-08-26
// Практическое занятие 11, задача 2

#include <iostream>  
using namespace std;

int a[1000];          


int countDays(int n, int x) {
    int days = 1;          // первый день
    int first = a[0];      // самый лёгкий пирожок текущего дня
    for (int i = 1; i < n; i++) {   
        if (a[i] - first > x) {     
            days++;                 
            first = a[i];           
        }
    }
    return days;           
}

int main() {
    int n, d;                                  // n - пирожков, d - дней
    cout << "Введите N и D: ";
    cin >> n >> d;

    cout << "Введите калорийность пирожков: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    // Сортировка пузырьком по возрастанию
    for (int i = 0; i < n - 1; i++) {          
        for (int j = 0; j < n - 1 - i; j++) {  
            if (a[j] > a[j + 1]) {             
                int t = a[j];                  
                a[j + 1] = t;
            }
        }
    }

    // Ищем ответ двоичным поиском: ответ лежит между 0 и (max - min)
    int left = 0;                     
    int right = a[n - 1] - a[0];      

    while (left < right) {            
        int mid = (left + right) / 2; 
        if (countDays(n, mid) <= d)   
            right = mid;              
        else
            left = mid + 1;            больше
    }

    cout << "Минимальная разница: " << left << "\n"; // left == right - это ответ
    return 0;
}
