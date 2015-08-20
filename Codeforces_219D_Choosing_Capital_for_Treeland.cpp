#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 200010;
const int INF = 0x3f3f3f3f;

struct Edge {
    int v, w;
    Edge() {}
    Edge(int _v, int _w) : v(_v), w(_w) {}
};
vector<Edge> G[MAXN];

int n, sum, dp[MAXN];
bool visited[MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) {
        G[i].clear();
    }
    memset(visited, false, sizeof(visited));
    sum = 0;
}

void input() {
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        G[a].push_back(Edge(b, 0));  // a -> b
        G[b].push_back(Edge(a, 1));  // b -> a
    }
}

void dfs1(int u) {  // 求根节点到所有点需要改变的边的条数
    visited[u] = true;
    for (int i = 0; i < G[u].size(); i++) {
        if (!visited[G[u][i].v]) {
            dfs1(G[u][i].v);
            sum += G[u][i].w;
        }
    }
}

void dfs2(int u) {  // 求节点到所有的点需要改变的边的条数
    visited[u] = true;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].v;
        if (!visited[v]) {
            if (G[u][i].w == 0) {
                dp[v] = dp[u] + 1;
            } else {
                dp[v] = dp[u] - 1;
            }
            dfs2(v);
        }
    }
}

void solve() {
    dfs1(1);

    memset(visited, false, sizeof(visited));
    dp[1] = sum;
    dfs2(1);

    int Min = INF;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (dp[i] < Min) {
            ans.clear();
            ans.push_back(i);
            Min = dp[i];
        } else if (dp[i] == Min) {
            ans.push_back(i);
        }
    }

    printf("%d\n", Min);
    for (int i = 0; i < ans.size()-1; i++) {
        printf("%d ", ans[i]);
    }
    printf("%d\n", ans[ans.size()-1]);
}

int main() {
    while (~scanf("%d", &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
