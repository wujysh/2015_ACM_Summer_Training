#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 1010;
const int MAXM = 50010;
const int INF = 0x3f3f3f3f;

typedef long long ll;

struct Edge {
    int to, cap, flow, cost, next;
    Edge() {}
    Edge(int _to, int _cap, int _cost, int _next) : to(_to), cap(_cap), cost(_cost), next(_next) { flow = 0; }
} edge[MAXM];

int head[MAXN], tol, pre[MAXN], dis[MAXN];
bool vis[MAXN];
int N, n, val[MAXN];

void init(int n) {
    N = n;
    tol = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int cap, int cost) {
    edge[tol] = Edge(v, cap, cost, head[u]);
    head[u] = tol++;
    edge[tol] = Edge(u, 0, -cost, head[v]);
    head[v] = tol++;
}

bool spfa(int s, int t) {
    queue<int> q;
    for (int i = 0; i < N; i++) {
        dis[i] = INF;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (edge[i].cap > edge[i].flow &&
                    dis[v] > dis[u] + edge[i].cost ) {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if (pre[t] == -1) return false;
    else return true;
}

int minCostMaxflow(int s, int t, int &cost) {
    int flow = 0;
    cost = 0;
    while (spfa(s, t)) {
        int Min = INF;
        for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
            if (Min > edge[i].cap - edge[i].flow)
                Min = edge[i].cap - edge[i].flow;
        }
        for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
            edge[i].flow += Min;
            edge[i ^ 1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        flow += Min;
    }
    return flow;
}

int main() {
    while (~scanf("%d", &n)) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            sum += val[i];
        }
        int avg = sum / n;

        int s = 0, t = n + 1, tt = t + 1;
        init(tt + 1);

        for (int i = 1; i < n; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u++, v++;
            addedge(u, v, INF, w);
            addedge(v, u, INF, w);
        }

        for (int i = 1; i <= n; i++) {
            addedge(s, i, val[i], 0);
            addedge(i, t, 1, 0);
            addedge(i, tt, avg, 0);
        }
        addedge(t, tt, sum % n, 0);

        int ans;
        minCostMaxflow(s, tt, ans);
        printf("%d\n", ans);
    }
    return 0;
}
