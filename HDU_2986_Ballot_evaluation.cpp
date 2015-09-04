#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include <map>
using namespace std;

map<string, int> mp;
string line;

int p, g, cCase;

void init() {
    mp.clear();
}

void input() {
    for (int i = 0; i < p; i++) {
        char str[55];
        int _i, _f;
        scanf("%s %d.%d", str, &_i, &_f);
        string name(str);
        mp[name] = _i * 10 + _f;
    }
}

void solve() {
    getchar();
    for (int i = 1; i <= g; i++) {
        getline(cin, line);
        stringstream ss(line);
        string str;
        int lvalue = 0;
        while (ss >> str) {
            if (str == "+") {
                continue;
            } else if (str[0] == '<' || str[0] == '>' || str[0] == '=') {
                break;
            } else {
                lvalue += mp[str];
            }
        }
        int value;
        bool flag = false;
        ss >> value;
        value *= 10;
        //cout << lvalue << " " << value << endl;
        if (str == "<") {
            if (lvalue < value) {
                flag = true;
            }
        } else if (str == ">") {
            if (lvalue > value) {
                flag = true;
            }
        } else if (str == "<=") {
            if (lvalue <= value) {
                flag = true;
            }
        } else if (str == ">=") {
            if (lvalue >= value) {
                flag = true;
            }
        } else if (str == "=") {
            if (lvalue == value) {
                flag = true;
            }
        }
        if (flag) {
            printf("Guess #%d was correct.\n", i);
        } else {
            printf("Guess #%d was incorrect.\n", i);
        }
    }
}

int main() {
    while (~scanf("%d%d", &p, &g)) {
        init();
        input();
        solve();
    }
    return 0;
}
