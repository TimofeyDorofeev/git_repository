#include <iostream>
#include <vector>
using namespace std;

int findMax(const vector<int>& numbers, int index) {
    if (index == static_cast<int>(numbers.size()) - 1) {
        return numbers[index];
    }

    int maxRemaining = findMax(numbers, index + 1);
    return numbers[index] > maxRemaining ? numbers[index] : maxRemaining;
}

int main() {
    int n;
    cin >> n;

    if (n <= 0) {
        cerr << "Array must not be empty" << endl;
        return 1;
    }

    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << findMax(numbers, 0) << endl;
    return 0;
}
