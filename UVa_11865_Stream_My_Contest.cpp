#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 40010;

struct Edge {
    int u, v, cost, bandwidth;
    Edge() {}
    Edge(int _u, int _v, int _cost, int _bandwidth) : u(_u), v(_v), cost(_cost), bandwidth(_bandwidth) {}
} edge[MAXM], e[MAXM];

int pre[MAXN], id[MAXN], visit[MAXN], in[MAXN], g[MAXN][MAXN], N, M, C, nCase;
vector<int> v;

int directed_mst(int root, int n, int m) {
    int res = 0, u, v;
    while (true) {
        for (int i = 0; i < n; i++) {
            in[i] = INF;
        }
        for (int i = 0; i < m; i++) {
            if (edge[i].u != edge[i].v && edge[i].cost < in[edge[i].v]) {
                pre[edge[i].v] = edge[i].u;
                in[edge[i].v] = edge[i].cost;
            }
        }
        for (int i = 0; i < n; i++) {
            if (i != root && in[i] == INF) {
                return INF;
            }
        }
        int tn = 0;
        memset(id, -1, sizeof(id));
        memset(visit, -1, sizeof(visit));
        in[root] = 0;
        for (int i = 0; i < n; i++) {
            res += in[i];
            v = i;
            while ( visit[v] != i && id[v] == -1 && v != root) {
                visit[v] = i;
                v = pre[v];
            }
            if ( v != root && id[v] == -1 ) {
                for (int u = pre[v]; u != v ; u = pre[u]) {
                    id[u] = tn;
                }
                id[v] = tn++;
            }
        }
        if (tn == 0) break;
        for (int i = 0; i < n; i++) {
            if (id[i] == -1) {
                id[i] = tn++;
            }
        }
        for (int i = 0; i < m;) {
            v = edge[i].v;
            edge[i].u = id[edge[i].u];
            edge[i].v = id[edge[i].v];
            if (edge[i].u != edge[i].v) {
                edge[i++].cost -= in[v];
            } else {
                swap(edge[i], edge[--m]);
            }
        }
        n = tn;
        root = id[root];
    }
    return res;
}

bool build(int cur) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            g[i][j] = INF;
        }
    }
    for (int i = 0; i < M; i++) {
        int u = e[i].u, v = e[i].v, cost = e[i].cost;
        if (u == v || e[i].bandwidth < cur) continue;
        g[u][v] = min(g[u][v], cost);
    }
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (g[i][j] < INF) {
                edge[cnt].u = i;
                edge[cnt].v = j;
                edge[cnt++].cost = g[i][j];
            }
        }
    }
    return directed_mst(0, N, cnt) <= C;
}

void init() {
    v.clear();
}

void input() {
    scanf("%d%d%d", &N, &M, &C);
    for (int i = 0; i < M; i++) {
        scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].bandwidth, &e[i].cost);
        v.push_back(e[i].bandwidth);
    }
}

void solve() {
    sort(v.begin(), v.end());
    if (!build(v[0])) {
        printf("streaming not possible.\n");
    } else {
        int l = 0, r = unique(v.begin(), v.end()) - v.begin() - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (build(v[mid])) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        printf("%d kbps\n", v[l]);
    }
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
