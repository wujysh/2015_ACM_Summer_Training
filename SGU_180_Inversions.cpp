#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 65540;

int n, a[MAXN], c[MAXN];
long long ans;
vector<int> v;

inline int lowbit(int x) {
    return x & (-x);
}

void update(int i, int val) {
    while (i < MAXN) {
        c[i] += val;
        i += lowbit(i);
    }
}

long long query(int i) {
    int s = 0;
    while (i > 0) {
        s += c[i];
        i -= lowbit(i);
    }
    return s;
}

void init() {
    ans = 0;
    v.clear();
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        v.push_back(a[i]);
    }
}

void solve() {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    }

    for (int i = n; i >= 1; i--) {
        ans += query(a[i] - 1);
        update(a[i], 1);
    }

    printf("%lld\n", ans);
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
