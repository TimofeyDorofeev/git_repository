// Дорофеев Тимофей Сергеевич группа ЭФБО-08-26

// задание 1

#include <iostream>                        
#include <vector>                          

using namespace std;                       


int findMax(const vector<int>& arr, int left, int right) {
    if (left == right) {                   
        return arr[left];                  
    }
    int mid = (left + right) / 2;          // Находим середину диапазона 
    int leftMax = findMax(arr, left, mid);     
    int rightMax = findMax(arr, mid + 1, right); 
    if (leftMax > rightMax) {              
        return leftMax;                    
    }
    return rightMax;                       
}

int main() {
    int n;                                 // Переменная для количества элементов
    cout << "Введите количество элементов: "; 
    cin >> n;                              

    if (n <= 0) {                          
        cout << "Ошибка: массив пуст" << endl; 
        return 1;                          
    }

    vector<int> arr(n);                    

    cout << "Введите элементы: ";          
    for (int i = 0; i < n; i++) {          
        cin >> arr[i];                     
    }

    cout << "Максимальный элемент: " << findMax(arr, 0, n - 1) << endl; // Запускаем рекурсию на всём массиве и выводим результат
    return 0;                              
}


// задание 2


#include <iostream>                    
#include <vector>                      
#include <cstdio>                      

using namespace std;                   

int main() {
    FILE* inFile = fopen("file_1.txt", "r"); // Открываем файл 
    if (inFile == NULL) {              
        cout << "Ошибка: не удалось открыть input.txt" << endl;
        return 1;                      
    }

    vector<string> lines;              // Вектор, в котором будем хранить все прочитанные строки
    char buffer[1024];                 // Буфер (массив символов) для временного хранения текущей строки (до 1023 символов)

    while (fgets(buffer, sizeof(buffer), inFile) != NULL) { // Читаем файл построчно
        string line = buffer;          // Преобразуем прочитанный буфер в объект string
        if (!line.empty() && line[line.size() - 1] == '\n') { 
            line.erase(line.size() - 1); 
        }
        lines.push_back(line);         
    }
    fclose(inFile);                    

    FILE* outFile = fopen("file_2.txt", "w"); 

    if (outFile == NULL) {            
        cout << "Ошибка: не удалось открыть output.txt" << endl; 
        return 1;                      
    }

    for (int i = (int)lines.size() - 1; i >= 0; i--) { 
        fputs(lines[i].c_str(), outFile); // Записываем текущую строку в выходной файл
        fputs("\n", outFile);          // Записываем перевод строки после неё
    }
    fclose(outFile);                   // Закрываем выходной файл — данные сохраняются на диск

    cout << "Готово! Строки записаны в output.txt в обратном порядке." << endl; 
    return 0;                          
}



// задание 3

#include <iostream>                    

using namespace std;                   

int main() {
    int arr[3];                        // Массив из трёх чисел

    cout << "Введите три числа: ";     
    for (int i = 0; i < 3; i++) {      
        cin >> arr[i];                 
    }

    
    for (int i = 0; i < 2; i++) {              
        for (int j = 0; j < 2 - i; j++) {      
            if (arr[j] > arr[j + 1]) {         
                int temp = arr[j];             
                arr[j] = arr[j + 1];           
                arr[j + 1] = temp;             
            }
        }
    }

    cout << "По возрастанию: ";        
    for (int i = 0; i < 3; i++) {      
        cout << arr[i] << " ";        
    }
    cout << endl;                      
    return 0;                          
}


