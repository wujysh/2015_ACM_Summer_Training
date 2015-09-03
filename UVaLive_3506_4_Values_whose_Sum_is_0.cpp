#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 4010;

int nCase, cCase, n, a[5][MAXN], ans;
vector<int> v;

void init() {
    v.clear();
    ans = 0;
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &a[j][i]);
        }
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            v.push_back(a[0][i] + a[1][j]);
        }
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = -(a[2][i] + a[3][j]);
            int l = lower_bound(v.begin(), v.end(), x) - v.begin();
            int r = upper_bound(v.begin(), v.end(), x) - v.begin();
            if (l < r && v[l] == x && v[r-1] == x) {
                ans += r - l;
            }
        }
    }

    if (++cCase > 1) printf("\n");
    printf("%d\n", ans);
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
