#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream input("input.txt");
    if (!input.is_open()) {
        cerr << "Не удалось открыть input.txt" << endl;
        return 1;
    }

    vector<string> lines;
    string line;

    while (getline(input, line)) {
        lines.push_back(line);
    }

    ofstream output("output.txt");
    if (!output.is_open()) {
        cerr << "Не удалось открыть output.txt" << endl;
        return 1;
    }

    for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
        output << *it << '\n';
    }

    return 0;
}
