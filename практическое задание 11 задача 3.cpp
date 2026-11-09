// Дорофеев Тимофей Сергеевич ЭФБО-08-26
// Практическое занятие 11, задача 3

#include <iostream>   
using namespace std;

int cost[100];        // стоимость каждого вида растения (N <= 100)

int main() {
    int n, k, l;   // n - видов растений, k - растений в букете, l - максимум одинаковых
    cout << "Введите N, K и L: ";
    cin >> n >> k >> l;

    cout << "Введите стоимости растений: ";
    for (int i = 0; i < n; i++)
        cin >> cost[i];

    // Сортировка пузырьком по убыванию: самые дорогие растения окажутся в начале
    for (int i = 0; i < n - 1; i++) {          
        for (int j = 0; j < n - 1 - i; j++) {  
            if (cost[j] < cost[j + 1]) {       
                int t = cost[j];               
                cost[j] = cost[j + 1];
                cost[j + 1] = t;
            }
        }
    }

    int total = 0;   // общая стоимость букета
    int left = k;    // сколько растений ещё нужно положить в букет

    for (int i = 0; i < n && left > 0; i++) {  // идём от самого дорогого вида
        int take = l;              
        if (left < take)           
            take = left;           
        total += take * cost[i];   
        left -= take;              
    }

    if (left > 0)   // растения кончились, а букет не собран (N * L < K)
        cout << "Собрать букет из K растений невозможно\n";
    else
        cout << "Максимальная стоимость букета: " << total << "\n";
    return 0;
}
