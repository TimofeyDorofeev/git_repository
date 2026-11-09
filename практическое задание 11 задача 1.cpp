// Дорофеев Тимофей Сергеевич ЭФБО-08-26
// Практическое занятие 11, задача 1: маршрут с максимальной суммой баллов

#include <iostream>   
using namespace std;  

int a[100][100];      // карта 
int dp[100][100];     // dp[i][j] - максимальная сумма баллов при приходе в клетку (i, j)
int pathI[200];       // номера строк клеток пути 
int pathJ[200];       // номера столбцов клеток пути

int main() {
    int n, m;                        // n - количество строк, m - количество столбцов
    cout << "Введите N и M: ";       // ввод размеров карты
    cin >> n >> m;                   

    cout << "Введите карту баллов:\n";
    for (int i = 0; i < n; i++)          
        for (int j = 0; j < m; j++)      
            cin >> a[i][j];              

    dp[0][0] = a[0][0]; 

    // Верхняя строка
    for (int j = 1; j < m; j++)
        dp[0][j] = dp[0][j - 1] + a[0][j];

    // Левый столбец
    for (int i = 1; i < n; i++)
        dp[i][0] = dp[i - 1][0] + a[i][0];

    // Остальные клетки
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            int best = dp[i - 1][j];      
            if (dp[i][j - 1] > best)      
                best = dp[i][j - 1];      
            dp[i][j] = best + a[i][j];    
        }
    }

    // Восстанавливаем путь
    int len = 0;         
    int i = n - 1;       
    int j = m - 1;

    while (true) {
        pathI[len] = i;              
        pathJ[len] = j;
        len++;                       
        if (i == 0 && j == 0)        
            break;
        if (i == 0)                  
        else if (j == 0)             
            i--;
        else if (dp[i - 1][j] >= dp[i][j - 1]) 
            i--;
        else                         
            j--;
    }

    // Путь записан задом наперёд (от финиша к старту), выводим его с конца
    cout << "Маршрут:\n";
    for (int k = len - 1; k >= 0; k--)
        cout << pathI[k] << " " << pathJ[k] << "\n";

    cout << "Максимальная сумма баллов: " << dp[n - 1][m - 1] << "\n";
    return 0;
}
