#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 100010;

struct Edge {
	int v, w, id, next;
	Edge() {}
	Edge(int _v, int _w, int _id, int _next) : v(_v), w(_w), id(_id), next(_next) {}
} edge[MAXN << 1];
int head[MAXN], cnt;

int n, m, K, p[MAXN], dis[MAXN], dp[MAXN], pre[MAXN];
bool valid[MAXN], vis[MAXN];
vector<int> ans;

void addEdge(int u, int v, int w, int id) {
    edge[cnt] = Edge(v, w, id, head[u]);
    head[u] = cnt++;
}

void dijkstra(int start) {
    priority_queue<pair<int, int> > q;
    for (int i = 0; i <= n; i++) {
        dis[i] = INF;
        vis[i] = false;
    }
    dis[start] = 0;
    q.push(make_pair(0, start));

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        vis[u] = true;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v, w = edge[i].w;
            if (!vis[v] && dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                q.push(make_pair(-dis[v], v));
            }
        }
    }
}

int DP(int u) {
    if (dp[u] != -1) return dp[u];

    dp[u] = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v, w = edge[i].w;
        if (dis[v] + w == dis[u]) {
            int cnt = DP(v);
            if (cnt > dp[u]) {
                dp[u] = cnt;
                pre[u] = i;
            }
        }
    }
    if (valid[u]) dp[u]++;
    return dp[u];
}

void output(int x) {
    if (x != -1) {
        output(pre[edge[x].v]);
    }
    if (edge[x].id) {
        ans.push_back(edge[x].id);
    }
}

void init() {
    memset(head, -1, sizeof(head));
    memset(dp, -1, sizeof(dp));
    memset(valid, false, sizeof(valid));
    memset(pre, -1, sizeof(pre));
    ans.clear();
    cnt = 0;
}

void input() {
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(a, b, c, i+1);
        addEdge(b, a, c, i+1);
    }
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        scanf("%d", &p[i]);
        valid[p[i]] = true;
    }
}

void solve() {
    dijkstra(p[0]);

    int start = p[0];
    for (int i = 0; i < K; i++) {
        if (dis[p[i]] > dis[start]) {
            start = p[i];
        }
    }

    dijkstra(start);
    int end = start;
    for (int i = 0; i < K; i++) {
        if (dis[p[i]] > dis[end]) {
            end = p[i];
        }
    }

    dp[start] = 1;
	DP(end);

	output(pre[end]);
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size()-1; i++) {
        printf("%d ", ans[i]);
	}
	printf("%d\n", ans.back());
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        init();
        input();
        solve();
    }
    return 0;
}
