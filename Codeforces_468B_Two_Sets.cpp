#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    for (int i = 0; i < n; i++) {
        if (visited[] == -1) {
            visited[i] = 0;
            visited[a - i] = 0;
            while (true) {
                int t = b - i;
            }
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)

const int N = 101000;
map<int, int> hs;

int n, a, b, f[N], vs[N], sta[N], p[N];
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
int main() {
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        father[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        if (mp.find(a - p[i]) != mp.end()) {
            father[find_set(a - p[i])] = find_set(i)
        }
    }


    rep(i, 1, n + 1) scanf("%d", p + i), hs[p[i]] = i, f[i] = i;
    rep(i, 1, n + 1) {
        if (hs.count(a - p[i])) f[find(hs[a - p[i]])] = find(i), vs[i] |= 1;
        if (hs.count(b - p[i])) f[find(hs[b - p[i]])] = find(i), vs[i] |= 2;
    }
    rep(i, 1, n + 1) sta[i] = 3;
    rep(i, 1, n + 1) sta[find(i)] &= vs[i];
    rep(i, 1, n + 1) if (sta[i] == 0) {
        puts("NO");
        return 0;
    }
    puts("YES");
    rep(i, 1, n + 1) {
        int st = sta[find(i)];
        putchar('0' + ((st & 1) == 0));
        if (i != n) putchar(' ');
    }
    puts("");
}
