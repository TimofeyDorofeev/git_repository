// Задача №1
#include <iostream> 
using namespace std; 

// СПОСОБ 1
long long powRec(long long a, int n) { // функция возвращает а в степени n
    if (n == 0) return 1; 
    long long half = powRec(a, n / 2); 
    if (n % 2 == 0) return half * half; 
    return half * half * a; 

// СПОСОБ 2
long long powIter(long long a, int n) { 
    long long result = 1; 
    while (n > 0) { 
        if (n % 2 == 1) result = result * a; 
        a = a * a;
        n = n / 2; 
    }
    return result; // возвращаем готовый ответ
}

int main() { 
    long long a; // основание степени
    int n; // показатель степени
    cin >> a >> n; 
    cout << powRec(a, n) << endl; 
    cout << powIter(a, n) << endl; 
    return 0; 
}



// Задача №2
#include <iostream> 
using namespace std; 

int gcd(int a, int b) { // функция возвращает НОД чисел a и b
    if (b == 0) return a; 
    return gcd(b, a % b); 
}

int main() { 
    int a, b; 
    cin >> a >> b; 
    cout << gcd(a, b) << endl; 
    return 0; 
}


// Задача №3
#include <iostream> 
using namespace std; 

// переложить n верхних ингредиентов с салфетки from на салфетку to, используя салфетку help
void hanoi(int n, int from, int to, int help) {
    if (n == 0) return; // нечего перекладывать — выходим из рекурсии
    hanoi(n - 1, from, help, to); // шаг 1: убираем n-1 меньших ингредиентов на вспомогательную салфетку
    cout << "Ingredient " << n << " move from " << from << " to " << to << endl; // шаг 2: кладём самый большой (n-й) на нужную салфетку
    hanoi(n - 1, help, to, from); // шаг 3: кладём n-1 меньших сверху на него
}

int main() { 
    int n;
    cin >> n; 
    hanoi(n, 1, 3, 2); 
    return 0; 
}
