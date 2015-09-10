#include <iostream>
#include <cstdio>
using namespace std;

int n;

int main() {
    while (cin >> n) {
        int cCase = 0;
        while (n--) {
            string str;
            cin >> str;
            cout << "String #" << ++cCase << endl;
            for (int i = 0; i < str.size(); i++) {
                if (str[i] == 'Z') {
                    cout << 'A';
                } else {
                    cout << char(str[i] + 1);
                }
            }
            cout << endl << endl;
        }
    }
    return 0;
}
