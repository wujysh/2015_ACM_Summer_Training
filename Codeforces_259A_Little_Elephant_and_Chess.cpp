#include <iostream>
#include <string>
using namespace std;

string line;

int main() {
    for (int i = 0; i < 8; i++) {
        getline(cin, line);
        if (line != "WBWBWBWB" && line != "BWBWBWBW") {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}
