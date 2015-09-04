#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 10010;
const int MAXM = 110;
const int INF = 0x3f3f3f3f;

int st[MAXM], g[MAXM][MAXM], dis[MAXN], n, m, num;
bool inQueue[MAXN];

struct Edge {
    int v, w;
    Edge() {}
    Edge(int _v, int _w) : v(_v), w(_w) {}
};
vector<Edge> G[MAXN];

map<int, int> mp;
queue<int> q;

void spfa(int start) {
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        inQueue[i] = 0;
    }
    dis[start] = 0;
    inQueue[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = 0;

        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].v, cost = G[u][i].w;
            if (dis[v] > dis[u] + cost) {
                dis[v] = dis[u] + cost;
                if (!inQueue[v]) {
                    inQueue[v] = true;
                    q.push(v);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dis[i] <= 600) {
            g[mp[start]][mp[i]] = 1;
        }
    }
}

void floyd() {
    for (int k = 0; k <= num + 1; k++) {
        for (int i = 0; i <= num + 1; i++) {
            for (int j = 0; j <= num + 1; j++) {
                if (g[i][j] > g[i][k] + g[k][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}

void init() {
    mp.clear();
    for (int i = 0; i <= n; i++) {
        G[i].clear();
    }
    for (int i = 0; i <= num + 2; i++) {
        for (int j = 0; j <= num + 2; j++) {
            g[i][j] = INF;
            if (i == j) g[i][j] = 0;
        }
    }
}

void input() {
    for (int i = 1; i <= num; i++) {
        scanf("%d", &st[i]);
        mp[st[i]] = i;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        scanf("%d%d%d", &u, &v, &cost);
        G[u].push_back(Edge(v, cost));
        G[v].push_back(Edge(u, cost));
    }
}

void solve() {
    st[0] = 1;
    mp[1] = 0;
    st[num + 1] = n;
    mp[n] = num + 1;

    for (int i = 0; i <= num; i++) {
        spfa(st[i]);
    }
    floyd();

    if (g[0][num + 1] == INF) {
        cout << -1 << endl;
    } else {
        cout << g[0][num + 1] - 1 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n) {
        cin >> num;
        init();
        input();
        solve();
    }
    return 0;
}
