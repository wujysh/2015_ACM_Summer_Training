#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 1000010;

struct Edge {
    int v, next;
    Edge() {}
    Edge(int _v, int _next) : v(_v), next(_next) {}
} edge[MAXN];
int head[MAXN], cnt;

int N, M, dcnt, st[MAXN], dfn[MAXN], low[MAXN];
bool apple[MAXN];

void init() {
    dcnt = N;
    cnt = 0;
    memset(head, -1, sizeof(head));
}

void add_edge(int u, int v) {
    edge[cnt] = Edge(v, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(u, head[v]);
    head[v] = cnt++;
}

void input() {
    int u, v;
    for (int i = 0; i < N-1; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
}

void dfs(int u, int fa) {
    dfn[u] = low[u] = dcnt--;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v == fa) continue;
        dfs(v, u);
        low[u] = min(low[u], low[v]);
    }
}

void update(int x, int c) {
    int i = x;
    while (i <= N) {
        st[i] += c;
        i += i & (-i);
    }
}

int query(int x) {
    int ret = 0, i = x;
    while (i > 0) {
        ret += st[i];
        i -= i & (-i);
    }
    return ret;
}

void solve() {
    dfs(1, -1);
    for (int i = 1; i <= N; i++) {
        update(dfn[i], 1);
        apple[i] = true;
    }

    scanf("%d", &M);
    while (M--) {
        int x;
        char op;
        getchar();
        scanf("%c", &op);
        if (op == 'Q') {
            scanf("%d", &x);
            printf("%d\n", query(dfn[x]) - query(low[x]-1));
        } else if (op == 'C') {
            scanf("%d", &x);
            if (apple[x]) {
                apple[x] = false;
                update(dfn[x], -1);
            } else {
                apple[x] = true;
                update(dfn[x], 1);
            }
        }
    }
}

int main() {
    while (~scanf("%d", &N)) {
        init();
        input();
        solve();
    }
    return 0;
}
