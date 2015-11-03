#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 20010;
const int MAXM = 880000;

struct Edge {
    int u, v, c, next;
    Edge(int u0 = 0, int v0 = 0, int c0 = 0, int next0 = 0) {
        u = u0;
        v = v0;
        c = c0;
        next = next0;
    }
} edge[MAXM];

int head[MAXN], cnt;
bool visited[MAXN];
int path[MAXN], d[MAXN], from, to, maxflow, offflow, n, m;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    maxflow = 0;
}

void addEdge(int u, int v, int c) {
    edge[cnt] = Edge(u, v, c, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, head[v]);
    head[v] = cnt++;
}

void input() {
    from = 0;
    to = n + 2;

    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        addEdge(from, i, a);
        addEdge(i, to, b);
    }
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        addEdge(a, b, w);
        addEdge(b, a, w);
    }
}

bool bfs() {
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(from);
    d[from] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].c && !d[v]) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[to];
}

int dfs(int x, int pf) {
    if (x == to) return pf;
    int ret = 0;
    for (int i = head[x]; i != -1 && pf ; i = edge[i].next) {
        int v = edge[i].v;
        if (edge[i].c && d[v] == d[x] + 1) {
            int p = dfs(v, min(edge[i].c, pf));
            edge[i].c -= p;
            edge[i ^ 1].c += p;
            ret += p;
            pf -= p;
        }
    }
    if (!ret) d[x] = -2;
    return ret;
}

int dinic() {
    int ret = 0;
    while (bfs()) ret += dfs(from, INF);
    return ret;
}

void output() {
    printf("%d\n", dinic());
}

int main() {
    while (~scanf("%d %d", &n, &m)) {
        init();
        input();
        output();
    }
    return 0;
}
