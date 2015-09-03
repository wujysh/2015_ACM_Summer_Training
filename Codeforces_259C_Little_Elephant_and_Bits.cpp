#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int MAXN = 100010;

string line;

int main() {
    getline(cin, line);

    int index = 0;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '0') {
            index = i;
            break;
        }
    }

    cout << line.substr(0, index) << line.substr(index+1) << endl;

    return 0;
}
