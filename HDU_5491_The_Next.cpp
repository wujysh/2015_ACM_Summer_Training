#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
using namespace std;

int num, S1, S2, cCase, nCase;
vector<int> a;

void init() {
    a.clear();
}

void input() {
    scanf("%d%d%d", &num, &S1, &S2);
}

void solve() {
    int ct = 0;
    while (num) {
        int t = num % 2;
        if (t == 1) ct++;
        a.push_back(t);
        num /= 2;
    }

    if (ct < S2 && !a[0]) {
        a[0] = 1;
    } else {
        bool flag = 0;
        int index = -1, len = a.size();
        for (int i = 0; i < len; i++) {
            if (a[i] && !flag) {
                flag = 1;
                while (i < len && a[i]) {
                    ct--;
                    a[i] = 0;
                    i++;
                }
                index = i;
            }
        }
        if (index >= len) {
            a.push_back(1);
        } else {
            a[index] = 1;
        }
        ct++;
        for (int i = 0; i < S1 - ct; i++) {
            a[i] = 1;
        }
    }

    ll ans = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        ans = ans * 2 + a[i];
    }
    printf("Case #%d: %I64d\n", ++cCase, ans);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
