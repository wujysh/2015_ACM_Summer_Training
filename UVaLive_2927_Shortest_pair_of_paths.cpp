#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

int gcd(int a, int b) {
    return a % b == 0 ? b : gcd(b, a % b);
}

#define MAXN 140
const int INF = 0x3f3f3f3f ;
int N, M;
queue<int>q;

struct node {
    int u, v, next;
    int flow, cap, cost;
} edge[MAXN * MAXN * 4];
int cnt, src, tag;
int C, F;
bool inq[MAXN];
int d[MAXN];
int head[MAXN], p[MAXN];

void add(int u, int v, int cap, int cost) {
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].cap = cap;
    edge[cnt].flow = 0;
    edge[cnt].cost = cost;
    edge[cnt].next = head[u];
    head[u] = cnt++;
    //反向
    edge[cnt].v = u;
    edge[cnt].u = v;
    edge[cnt].flow = 0;
    edge[cnt].cap = 0;
    edge[cnt].cost = - cost;
    edge[cnt].next = head[v];
    head[v] = cnt++;
}
void read() {
    cnt = 0;
    memset(head, -1, sizeof(head));
    src = 0;
    tag = N + 1;
    add(src, 1, 2, 0);
    //for (int i = 1; i <= N; i++)  add(i,i + N,1,0);
    for (int i = 1; i <= M; i++) {
        int u , v , w;
        scanf("%d%d%d", &u, &v, &w);
        u++;
        v++;
        //u的后向点 链接 v 的前向点
        add(u, v, 1, w);
    }
    add(N, tag, 2, 0);
}
bool SPFA(int s, int t) {
    while (!q.empty()) q.pop();
    memset(inq, false, sizeof(inq));
    memset(d, 0x3f, sizeof(d));
    memset(p, -1, sizeof(p));
    d[s] = 0;
    q.push(s);
    inq[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v;
            if (d[v] > d[u] + edge[i].cost && edge[i].cap > edge[i].flow) {
                d[v] = d[u] + edge[i].cost;
                p[v] = i;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return d[tag] != INF;
}
void solve() {
    C = F = 0;
    while(SPFA(src, tag)) {
        int a = INF;
        for (int i = p[tag]; i != -1; i = p[edge[i].u])
            a = min(a, edge[i].cap - edge[i].flow);
        for (int i = p[tag]; i != -1; i = p[edge[i].u]) {
            edge[i].flow += a;
            edge[i ^ 1].flow -= a;
        }
        C += d[tag] * a;
        F += a;
    }
}
int main() {
    int kase = 1;
    while (scanf("%d%d", &N, &M) != EOF) {
        if (N == 0 && M == 0) break;
        read();
        solve();
        if (F < 2) printf("Instance #%d: Not possible\n", kase++);
        else printf("Instance #%d: %d\n", kase++, C);
    }
    return 0;
}
