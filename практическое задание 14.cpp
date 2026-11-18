// задание 1


#include <iostream>              
using namespace std;             

int main() {
    char s[1001];                // строка
    cin.getline(s, 1001);        

    char st[1001];               
    int top = 0;                 // сколько скобок сейчас в стеке
    bool ok = true;              // пока считаем, что последовательность правильная

    for (int i = 0; s[i] != '\0' && ok; i++) { 
        char c = s[i];           // текущий символ

        if (c == '(' || c == '[' || c == '{') {
            st[top++] = c;       
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == 0) {      
                ok = false;      
            } else {
                char open = st[--top]; 
                if ((c == ')' && open != '(') || 
                    (c == ']' && open != '[') ||
                    (c == '}' && open != '{'))
                    ok = false;  // открыли '(' а закрыли ']' — ошибка
            }
        }
        
    }

    if (ok && top == 0)          
        cout << "yes";           
    else
        cout << "no";            

    return 0;                    
}


// задание 2

#include <iostream>
using namespace std;

int main() {
    char words[1000][1001];      
    int n = 0;                   
    char line[10001];            

    while (cin.getline(line, 10001)) { 
        char word[1001];         
        int len = 0;            

        for (int i = 0; ; i++) { // идём по символам строки
            char c = line[i];    // текущий символ

            bool letter = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                          (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я') ||
                          c == 'ё' || c == 'Ё' || c == '-';

            if (letter) {
                if (c >= 'A' && c <= 'Z') c = c + 32; 
                                                     
                if (c >= 'А' && c <= 'Я') c = c + 32; 
                if (c == 'Ё') c = 'ё';                

                if (c == '-' && len == 0) continue;   
                word[len++] = c;                      
            }

        
            if (!letter || c == '\0') {
                if (len > 0 && word[len - 1] == '-') len--; 
                if (len > 0) {                        
                    word[len] = '\0';                 
                    
                    // посимвольно сравниваем слова
                    bool found = false;               
                    for (int j = 0; j < n; j++) {     
                        bool same = true;             
                        for (int k = 0; word[k] != '\0' || words[j][k] != '\0'; k++)
                            if (word[k] != words[j][k]) { 
                                same = false;             
                                break;                    
                            }
                        if (same) { found = true; break; } 
                    }

                    if (!found) {                     
                        for (int k = 0; k <= len; k++)
                            words[n][k] = word[k];    // копируем слово в хранилище
                        n++;                          // увеличиваем счётчик уникальных слов
                    }
                }
                len = 0;                              // начинаем собирать следующее слово с нуля
                if (c == '\0') break;                 // если строка кончилась — выходим из цикла
            }
        }
    }

    for (int i = 0; i < n; i++)  
        cout << words[i] << "\n";

    return 0;
}


// задание 3

#include <iostream>
using namespace std;

bool eq(const char* a, const char* b) {
    int i = 0;                                  
    while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
        i++;                                    
    return a[i] == b[i] && a[i] == '\0';        
}

class MinStack {
    int data[100000];   // основной стек
    int mins[100000];   
    int top = 0;        

public:
    void push(int x) {                       
        if (top == 0)                         
            mins[top] = x;                    
        else
            mins[top] = (x < mins[top - 1]) ? x : mins[top - 1];
        data[top++] = x;                      
    }

    int pop() {                               
        return data[--top];                   
    }

    int getMin() {                            
        return mins[top - 1];                 
    }

    bool empty() {                            
        return top == 0;                      
    }
};

int main() {
    MinStack st;                 
    char cmd[20];                

    while (cin >> cmd) {         
        if (eq(cmd, "push")) {   
            int x;
            cin >> x;            
            st.push(x);
        } else if (eq(cmd, "pop")) {  
            if (!st.empty())          
                st.pop();
            else
                cout << "stack is empty\n"; 
        } else if (eq(cmd, "min")) {  
            if (!st.empty())
                cout << st.getMin() << "\n";    
            else
                cout << "stack is empty\n";
        } else if (eq(cmd, "empty")) { 
            cout << (st.empty() ? "yes" : "no") << "\n"; 
        }
    }
    return 0;
}
