#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 10010;
const int MAXM = 50010;

struct Edge {
    int v, w, next;
    Edge() {}
    Edge(int _v, int _w, int _next) : v(_v), w(_w), next(_next) {}
} edge[MAXM];
int head[MAXN], cnt;

int sz[MAXN], max_size[MAXN], dis[MAXN], min_max_size, root, num, n, k, ans;
bool visited[MAXN];

void addEdge(int u, int v, int w) {
    edge[cnt] = Edge(v, w, head[u]);
    head[u] = cnt++;
}

void dfs_size(int u, int fa) {
    sz[u] = 1;
    max_size[u] = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v != fa && !visited[v]) {
            dfs_size(v, u);
            sz[u] += sz[v];
            if (sz[v] > max_size[u]) {
                max_size[u] = sz[v];
            }
        }
    }
}

void dfs_root(int r, int u, int fa) {
    if (sz[r] - sz[u] > max_size[u]) {
        max_size[u] = sz[r] - sz[u];
    }
    if (max_size[u] < min_max_size) {
        min_max_size = max_size[u];
        root = u;
    }
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v != fa && !visited[v]) {
            dfs_root(r, v, u);
        }
    }
}

void dfs_dis(int u, int d, int fa) {
    dis[num++] = d;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v != fa && !visited[v]) {
            dfs_dis(v, d + edge[i].w, u);
        }
    }
}

int calc(int u, int d) {
    int ret = 0;
    num = 0;
    dfs_dis(u, d, 0);
    sort(dis, dis + num);
    int l = 0, r = num - 1;
    while (l < r) {
        while (dis[l] + dis[r] > k && l < r) {
            r--;
        }
        ret += r - l;
        l++;
    }
    return ret;
}

void dfs(int u) {
    min_max_size = n;
    dfs_size(u, 0);
    dfs_root(u, u, 0);
    ans += calc(root, 0);
    visited[root] = true;

    for (int i = head[root]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (!visited[v]) {
            ans -= calc(v, edge[i].w);
            dfs(v);
        }
    }
}

void init() {
    memset(head, -1, sizeof(head));
    memset(visited, false, sizeof(visited));
    cnt = 0;
    ans = 0;
}

void input() {
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
}

void solve() {
    dfs(1);
    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d%d", &n, &k) && (n || k)) {
        init();
        input();
        solve();
    }
    return 0;
}
