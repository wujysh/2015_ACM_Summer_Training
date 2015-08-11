#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int MAXN = 110;
string str[MAXN];
int n, m;

void input() {
    for (int i = 0; i < m; i++) {
        cin >> str[i];
    }
}

bool cmp(const string &a, const string &b) {
    int cntA = 0, cntB = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (a[i] > a[j]) {
                cntA++;
            }
            if (b[i] > b[j]) {
                cntB++;
            }
        }
    }
    return cntA < cntB;
}

void solve() {
    sort(str, str+m, cmp);
    for (int i = 0; i < m; i++) {
        cout << str[i] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m) {
        input();
        solve();
    }
    return 0;
}
