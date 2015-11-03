#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;

const double INF = 4000000;
const int MAXN = 220;
const int MAXM = 11010;

struct Edge {
    int u, v, next, c;
    double w;
    Edge() {}
    Edge(int _u, int _v, int _c, double _w, int _next) : u(_u), v(_v), c(_c), w(_w), next(_next) {}
} edge[MAXM * 4];

int head[MAXN], cnt;
bool visited[MAXN];
int path[MAXN], from, to, n;
double dist[MAXN];

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
} colony[MAXN], tree[MAXN];

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
}

void addEdge(int u, int v, int c, double w) {
    edge[cnt] = Edge(u, v, c, w, head[u]);
    head[u] = cnt++;
    edge[cnt] = Edge(v, u, 0, -w, head[v]);
    head[v] = cnt++;
}

inline double sqr(int x) {
    return x * x;
}

inline double dis(const Point &a, const Point &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &colony[i].x, &colony[i].y);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &tree[i].x, &tree[i].y);
    }

    from = 0;
    to = 2*n + 1;
    for (int i = 1; i <= n; i++) {
        addEdge(from, i, 1, 0);
        addEdge(n+i, to, 1, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            addEdge(i, j+n, 1, dis(colony[i], tree[j]));
        }
    }
}

bool findPath() {
    queue<int> q;
    memset(visited, false, sizeof(visited));
    memset(path, -1, sizeof(path));
    fill(dist, dist + MAXN, INF);
    dist[from] = 0;
    visited[from] = true;
    q.push(from);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (edge[i].c > 0 && dist[u] + edge[i].w < dist[v]) {
                dist[v] = dist[u] + edge[i].w;
                path[v] = i;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        visited[u] = false;
    }

    return dist[to] != INF;
}

double MinCostMaxFlow() {
    int offflow, maxflow = 0;
    double ret = 0;
    while (findPath()) {
        offflow = INF;
        for (int i = path[to]; i != -1; i = path[edge[i].u]) {
            offflow = min(offflow, edge[i].c);
        }
        for (int i = path[to]; i != -1; i = path[edge[i].u]) {
            edge[i].c -= offflow;
            edge[i ^ 1].c += offflow;
        }
        maxflow += offflow;
        ret += dist[to] * offflow;
    }
    return maxflow == n ? ret : -1;
}

void solve() {
    MinCostMaxFlow();
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i != -1; i = edge[i].next) {
            if (edge[i].c == 0) {
                printf("%d\n", edge[i].v - n);
                break;
            }
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
