#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
using namespace std;

map<char, char> m;
string line;

int main() {
    ios::sync_with_stdio(false);
    m['b'] = 'd';
    m['d'] = 'b';
    m['p'] = 'q';
    m['q'] = 'p';
    m['i'] = 'i';
    m['o'] = 'o';
    m['v'] = 'v';
    m['w'] = 'w';
    m['x'] = 'x';
    while (getline(cin, line) && line != "#") {
        bool flag = true;
        for (int i = 0; i < line.size(); i++) {
            if (m.find(line[i]) != m.end()) {
                line[i] = m[line[i]];
            } else {
                cout << "INVALID" << endl;
                flag = false;
                break;
            }
        }
        if (flag) {
            reverse(line.begin(), line.end());
            cout << line << endl;
        }
    }
    return 0;
}
