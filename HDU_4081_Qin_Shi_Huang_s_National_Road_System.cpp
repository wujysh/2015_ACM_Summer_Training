#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

struct City {
    double x, y;
    int p;
    City() {}
    City(double _x, double _y, int _p) : x(_x), y(_y), p(_p) {}
} city[MAXN];

int nCase, n;
double ans, maxcost[MAXN][MAXN], graph[MAXN][MAXN];

void init() {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            graph[i][j] = graph[j][i] = INF;
            maxcost[i][j] = maxcost[j][i] = 0;
        }
    }
    ans = 0;
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%d", &city[i].x, &city[i].y, &city[i].p);
    }
}

double dis(int c1, int c2) {
    return sqrt((city[c1].x - city[c2].x) * (city[c1].x - city[c2].x) + (city[c1].y - city[c2].y) * (city[c1].y - city[c2].y));
}

double prim() {
    double ret = 0;

    bool visited[MAXN];
    double dist[MAXN];
    int pre[MAXN], cur;
    vector<int> v;
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }

    visited[0] = true;
    dist[0] = 0;
    v.push_back(0);
    cur = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[cur][j] < dist[j]) {
                pre[j] = cur;
                dist[j] = graph[cur][j];
            }
        }
        double mindist = INF;
        int index = MAXN - 1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < mindist) {
                mindist = dist[j];
                index = j;
            }
        }
        ret += dist[index];
        cur = index;
        visited[index] = true;
        for (int j = 0, sz = v.size(); j < sz; j++) {
            maxcost[v[j]][index] = maxcost[index][v[j]] = max(maxcost[v[j]][pre[index]], dist[index]);
        }
        v.push_back(index);
    }
    return ret;
}

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            graph[i][j] = graph[j][i] = dis(i, j);
        }
    }

    double total = prim();

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            double a = city[i].p + city[j].p;
            double b = total - maxcost[i][j];
            ans = max(ans, a / b);
        }
    }

    printf("%.2lf\n", ans);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
