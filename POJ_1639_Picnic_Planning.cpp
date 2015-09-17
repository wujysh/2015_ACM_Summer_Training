#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 25;
const int INF = 1 << 30;

int cost[MAXN][MAXN], pre[MAXN], dis[MAXN];
bool vis[MAXN], tree[MAXN][MAXN];
int M, N, K, ans;

void input() {
    char s[20], e[20];
    int w, cont = 1;
    map<string, int> f;
    f.clear();
    f["Park"] = 0;
    memset(cost, 0x3f, sizeof(cost));
    while (M--) {
        scanf("%s%s%d", s, e, &w);
        if (f.find((string)s) == f.end())
            f[(string)s] = cont++;
        if (f.find((string)e) == f.end())
            f[(string)e] = cont++;
        int u = f[(string)s], v = f[(string)e];
        cost[u][v] = cost[v][u] = w;
    }
    N = cont;
    scanf("%d", &K);
}

int find_max(int s, int e, int &st, int &ed) { // BFS找到环上边权最大的边
    int que[MAXN + 10];
    memset(vis, false, sizeof(vis));
    vis[s] = true;
    int head = 0, tail = 0;
    pre[s] = -1;
    que[tail++] = s;
    while (tail > head) {
        int tep = que[head++];
        for (int i = 1; i < N; ++i) {
            if (!vis[i] && tree[tep][i]) {
                vis[i] = true;
                pre[i] = tep;
                que[tail++] = i;
            }
        }
    }
    int re = -1;
    while (s != e) {
        if (re < cost[e][pre[e]]) {
            re = cost[e][pre[e]];
            st = e;
            ed = pre[e];
        }
        e = pre[e];
    }
    return re;
}

int prim() {
    memset(vis, false, sizeof(vis));
    memset(tree, false, sizeof(tree));
    for (int i = 1; i < N; ++i) {
        pre[i] = 1;
        dis[i] = cost[1][i];
    }
    vis[1] = true;
    int sum = 0;
    for (int i = 1; i < N - 1; ++i) {
        int md = INF, idex = -1;
        for (int j = 1; j < N ; ++j) {
            if (!vis[j] && dis[j] < md) {
                md = dis[j];
                idex = j;
            }
        }
        if (idex == -1) break;
        vis[idex] = true;
        tree[idex][pre[idex]] = tree[pre[idex]][idex] = true;
        sum += md;
        for (int j = 1; j < N; ++j)
            if (!vis[j] && dis[j] > cost[idex][j]) {
                dis[j] = cost[idex][j];
                pre[j] = idex;
            }
    }
    return sum;
}

void solve() {
    ans = prim();          //先对剩余点求最小生成树
    int m = INF, idex = -1;
    for (int i = 1; i < N; ++i) {  // 然后从生成树中找一个距度限制点最近的点加进来
        if (cost[i][0] < m) {
            m = cost[i][0];
            idex = i;
        }
    }
    ans += m;
    tree[idex][0] = tree[0][idex] = true;
    for (int i = 1; i < K; ++i) {   //然后进行K-1次循环每次进行树的更新
        int st, ed, s, e;
        idex = -1;
        m = 0;
        for (int j = 1, k; j < N; ++j) {
            if (!tree[j][0]) {
                k = find_max(0, j, st, ed);
                if (m > cost[j][0] - k) {
                    m = cost[j][0] - k;
                    idex = j;
                    s = st;
                    e = ed;
                }
            }
        }
        if (idex == -1) break;
        ans += m;
        tree[idex][0] = tree[0][idex] = true;
        tree[s][e] = tree[e][s] = false;
    }
    printf("Total miles driven: %d\n", ans);
}

int main() {
    while (~scanf("%d", &M)) {
        input();
        solve();
    }
    return 0;
}
