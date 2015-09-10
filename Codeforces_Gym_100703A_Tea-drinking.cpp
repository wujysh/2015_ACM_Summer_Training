#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const int MAXM = 35;

char recipe[MAXN][MAXM];
int father[MAXN], rank_set[MAXN], ans, cnt, n, m;

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
    bool operator < (const Edge &t) const {
        return w < t.w;
    }
} edge[MAXN * MAXN];

int find_set(int x) {
    return x == father[x] ? x : x = find_set(father[x]);
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

void init() {
    ans = cnt = 0;
    for (int i = 0; i < n; i++) {
        father[i] = i;
        rank_set[i] = 1;
    }
}

void input() {
    getchar();
    for (int i = 0; i < n; i++) {
        scanf("%s", recipe[i]);
    }
}

int dis(int i, int j) {
    int ret = 0;
    for (int x = 0; x < m; x++) {
        ret = max(ret, abs(recipe[i][x] - recipe[j][x]));
    }
    return ret;
}

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            edge[cnt++] = Edge(i, j, dis(i, j));
        }
    }

    sort(edge, edge+cnt);

    for (int i = 0; i < cnt; i++) {
        int u = edge[i].u, v = edge[i].v;
        if (find_set(u) != find_set(v)) {
            union_set(u, v);
            ans = edge[i].w;
        }
    }

    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        init();
        input();
        solve();
    }
    return 0;
}
