#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 10010;
const int MAXH = 20;

vector<int> G[MAXN];
int n, m, ans[MAXN], inDegree[MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) {
        G[i].clear();
    }
    memset(ans, 0, sizeof(ans));
    memset(inDegree, 0, sizeof(inDegree));
}

void input() {
    int u, v, c;
    for (int i = 0; i < n; i++) {
        scanf("%d:(%d)", &u, &c);
        while (c--) {
            scanf("%d", &v);
            G[u].push_back(v);
            G[v].push_back(u);
            inDegree[v]++;
        }
    }
    scanf("%d", &m);
}

int anc[MAXN][MAXH], dep[MAXN];

void bfs(int root) {
    queue<int> q;
    dep[root] = 0;
    anc[root][0] = root;
    q.push(root);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 1; i < MAXH; i++) {
            anc[u][i] = anc[anc[u][i-1]][i-1];
        }
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (v == anc[u][0]) continue;
            dep[v] = dep[u] + 1;
            anc[v][0] = u;
            q.push(v);
        }
    }
}

int LCA(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int tu = u, tv = v;
    for (int det = dep[v] - dep[u], i = 0; det; det >>= 1, i++) {
        if (det & 1) {
            tv = anc[tv][i];
        }
    }
    if (tu == tv) return tu;
    for (int i = MAXH-1; i >= 0; i--) {
        if (anc[tu][i] == anc[tv][i]) continue;
        tu = anc[tu][i];
        tv = anc[tv][i];
    }
    return anc[tu][0];
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!inDegree[i]) {
            bfs(i);
        }
    }
    while (m--) {
        while (getchar() != '(');
        int u, v;
        scanf("%d%d", &u, &v);
        ans[LCA(u, v)]++;
        while (getchar() != ')');
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i]) {
            printf("%d:%d\n", i, ans[i]);
        }
    }
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
