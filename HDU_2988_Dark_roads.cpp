#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 200010;

struct Edge {
    int x, y, z;
    Edge() {}
    bool operator < (const Edge &b) const {
        return z < b.z;
    }
} edge[MAXN];

int n, m, father[MAXN], rank_set[MAXN], sum, ans;

void init() {
    for (int i = 0; i < m; i++) {
        father[i] = i;
        rank_set[i] = 1;
    }
    sum = ans = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &edge[i].x, &edge[i].y, &edge[i].z);
        sum += edge[i].z;
    }
}

int find_set(int x) {
    return x == father[x] ? x : father[x] = find_set(father[x]);
}

void union_set(int x, int y) {
    int a = find_set(x), b = find_set(y);
    if (a == b) return;
    if (rank_set[a] < rank_set[b]) {
        father[a] = b;
    } else {
        father[b] = a;
        if (rank_set[a] == rank_set[b]) {
            rank_set[a]++;
        }
    }
}

void solve() {
    sort(edge, edge+n);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (find_set(edge[i].x) != find_set(edge[i].y)) {
            union_set(edge[i].x, edge[i].y);
            ans += edge[i].z;
        }
    }

    printf("%d\n", sum - ans);
}

int main() {
    while (~scanf("%d%d", &m, &n) && (m || n)) {
        init();
        input();
        solve();
    }
    return 0;
}
