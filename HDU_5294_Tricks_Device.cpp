#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <set>
using namespace std;

const int MAXN = 2010;
const int MAXM = 60010;
const int INF = 0x3f3f3f3f;

/// SAP
struct Edge {
    int to, next, cap, flow;
    Edge() {}
    Edge(int _to, int _next, int _cap, int _flow) : to(_to), next(_next), cap(_cap), flow(_flow) {}
} edge[MAXM * 4];

int tot, head[MAXN];
int gap[MAXN], dep[MAXN], cur[MAXN], q[MAXN], S[MAXN];;

void addEdge(int u, int v, int w, int rw = 0) {
    edge[tot] = Edge(v, head[u], w, 0);
    head[u] = tot++;
    edge[tot] = Edge(u, head[v], rw, 0);
    head[v] = tot++;
}

void bfs(int start, int end) {
    memset(dep, -1, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    gap[0] = 1;
    int front = 0, rear = 0;
    dep[end] = 0;
    q[rear++] = end;
    while (front != rear) {
        int u = q[front++];
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (dep[v] != -1) continue;
            q[rear++] = v;
            dep[v] = dep[u] + 1;
            gap[dep[v]]++;
        }
    }
}

int SAP(int start, int end, int N) {
    bfs(start, end);
    memcpy(cur, head, sizeof(head));
    int top = 0;
    int u = start;
    int ans = 0;
    while (dep[start] < N) {
        if (u == end) {
            int Min = INF;
            int inser;
            for (int i = 0; i < top; i++) {
                if (Min > edge[S[i]].cap - edge[S[i]].flow) {
                    Min = edge[S[i]].cap - edge[S[i]].flow;
                    inser = i;
                }
            }
            for (int i = 0; i < top; i++) {
                edge[S[i]].flow += Min;
                edge[S[i] ^ 1].flow -= Min;
            }
            ans += Min;
            top = inser;
            u = edge[S[top] ^ 1].to;
            continue;
        }
        bool flag = false;
        int v;
        for (int i = cur[u]; i != -1; i = edge[i].next) {
            v = edge[i].to;
            if (edge[i].cap - edge[i].flow && dep[v] + 1 == dep[u]) {
                flag = true;
                cur[u] = i;
                break;
            }
        }
        if (flag) {
            S[top++] = cur[u];
            u = v;
            continue;
        }
        int Min = N;
        for (int i = head[u]; i != -1; i = edge[i].next)
            if (edge[i].cap - edge[i].flow && dep[edge[i].to] < Min) {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]]--;
        if (!gap[dep[u]]) {
            return ans;
        }
        dep[u] = Min + 1;
        gap[dep[u]]++;
        if (u != start) {
            u = edge[S[--top] ^ 1].to;
        }
    }
    return ans;
}

/// Dinic
int from, to, d[MAXN];

bool bfs() {
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(from);
    d[from] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (edge[i].cap && !d[v]) {
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
        int v = edge[i].to;
        if (edge[i].cap && d[v] == d[x] + 1) {
            int p = dfs(v, min(edge[i].cap, pf));
            edge[i].cap -= p;
            edge[i ^ 1].cap += p;
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

/// SPFA
struct Node {
    int v, cost;
    Node() {}
    Node(int _v, int _cost): v(_v), cost(_cost) {}
};
vector<Node> G[MAXN], G2[MAXN];

bool vis[MAXN];
int cnt[MAXN], dist[MAXN];

bool SPFA(int start, int n) {
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;

    q.push(start);
    vis[start] = true;
    dist[start] = 0;
    cnt[start] = 1;

    while (!q.empty())	{
        int u = q.front();
        q.pop();
        vis[u] = false;

        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].v;
            if (dist[v] > dist[u] + G[u][i].cost) {
                dist[v] = dist[u] + G[u][i].cost;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                    if (++cnt[v] > n) return false;
                }
            }
        }
    }
    return true;
}

/// main
set<int> s;
int m, n;

void init() {
    s.clear();
    tot = 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }
}

void input() {
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        G[a].push_back(Node(b, c));
        G[b].push_back(Node(a, c));
    }
}

void solve() {
    SPFA(1, n);
    for (int i = 1; i <= n; i++) {
        G2[i] = G[i];
        G[i].clear();
    }
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < G2[u].size(); i++) {
            int v = G2[u][i].v;
            if (dist[u] + G2[u][i].cost == dist[v]) {
                addEdge(u, v, 1);
                s.insert(u);
                s.insert(v);
                G[u].push_back(Node(v, 1));
            }
        }
    }
    //int ans = SAP(1, n, (int)s.size());
    from = 1;
    to = n;
    int ans = dinic();
    SPFA(1, n);
    printf("%d %d\n", ans, m - dist[n]);
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        init();
        input();
        solve();
    }
    return 0;
}
