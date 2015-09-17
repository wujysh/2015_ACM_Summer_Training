#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 110;

vector<int> G[MAXN];
int N, low[MAXN], dfn[MAXN], vis[MAXN];

struct Edge {
    int u, v;
    Edge() {}
    Edge(int _u, int _v) : u(_u), v(_v) {}
    bool operator < (const Edge &b) const {
        if (u == b.u) {
            return v < b.v;
        }
        return u < b.u;
    }
};
vector<Edge> links;

void init() {
    for (int i = 0; i < N; i++) {
        G[i].clear();
    }
    memset(vis, 0, sizeof(vis));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    links.clear();
}

void input() {
    int M, u, v;
    for (int i = 0; i < N; i++) {
        scanf("%d (%d)", &u, &M);
        for (int i = 0; i < M; i++) {
            scanf("%d", &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
}

void cut_bridge(int cur, int father, int dep) {
    vis[cur] = 1;
    dfn[cur] = low[cur] = dep;
    int children = 0;
    for (int i = 0; i < G[cur].size(); i++) {
        int v = G[cur][i];
        if (v != father && vis[v] == 1) {
            low[cur] = min(low[cur], dfn[v]);
        } else if (vis[v] == 0) {
            cut_bridge(v, cur, dep + 1);
            children++;
            low[cur] = min(low[cur], low[v]);
            if (low[v] > dfn[cur]) {
                links.push_back(Edge(min(cur, v), max(cur, v)));
            }
        }
    }
    vis[cur] = 2;
}

void solve() {
    for (int i = 0; i < N; i++) {
        if (vis[i] == 0) {
            cut_bridge(i, -1, 0);
        }
    }

    sort(links.begin(), links.end());

    printf("%d critical links\n", links.size());
    for (int i = 0; i < links.size(); i++) {
        printf("%d - %d\n", links[i].u, links[i].v);
    }
    printf("\n");
}

int main() {
    while (~scanf("%d", &N)) {
        init();
        input();
        solve();
    }
    return 0;
}
