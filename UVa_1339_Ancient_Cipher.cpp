#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;

const int N = 105;

char str[N];
int vis1[26], vis2[26];

bool judge() {
    for (int i = 0; i < 26; i++) {
        if (vis1[i] != vis2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    while (cin >> str) {
        memset(vis1, 0, sizeof(vis1));
        memset(vis2, 0, sizeof(vis2));
        for (int i = 0; i < strlen(str); i++) {
            vis1[str[i] - 'A'] ++;
        }
        sort(vis1, vis1 + 26);
        cin >> str;
        for (int i = 0; i < strlen(str); i++) {
            vis2[str[i] - 'A'] ++;
        }
        sort(vis2, vis2 + 26);
        if (judge()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
