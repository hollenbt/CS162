#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

int main() {
    srand(time(0));
    int n, sort_type;
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ofstream out(filename.c_str());

    cout << "Enter the number of test cases: ";
    cin >> n;

    cout << "Enter the sorting type (descending -1, random 0, ascending 1, uniform 2): ";
    cin >> sort_type;

    for (int i = 0; i < n; ++i) {
        if (sort_type == 0)
            out << 1 + rand() % n << " ";
        else if (sort_type == -1)
            out << n - i << " ";
        else if (sort_type == 1)
            out << i + 1 << " ";
        else out << 1 << " ";
    }

    out.close();

    return 0;
}
