#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const double INF = 1e30;
const double EPS = 1e-8;

struct Point {
    double x, y, z;
    Point() {}
    Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
} point[MAXN];

int n;
double cost[MAXN][MAXN], len[MAXN][MAXN], dist[MAXN];
bool visited[MAXN];

int cmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x > 0) return 1;
    return -1;
}

inline double sqr(double x) {
    return x * x;
}

inline double dis(Point &a, Point &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

/// ratio_mst
double prim(double k) {
    for (int i = 2; i <= n; i++) {
        dist[i] = cost[1][i] - k * len[1][i];
        visited[i] = false;
    }
    dist[1] = 0;
    visited[1] = true;

    double ans = 0.0;
    for (int i = 1; i <= n; i++) {
        double minDist = INF;
        int v = 0;
        for (int j = 2; j <= n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                v = j;
                minDist = dist[j];
            }
        }
        ans += dist[v];
        visited[v] = true;
        for (int j = 2; j <= n; j++) {
            if (!visited[j]) {
                if (dist[j] > cost[v][j] - k * len[v][j]) {
                    dist[j] = cost[v][j] - k * len[v][j];
                }
            }
        }
    }

    return ans;
}

double ratio_mst() {
    double l = 0, r = 1e6;
    while (cmp(r - l) > 0) {
        double mid = (l + r) / 2;
        if (prim(mid) < 0) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return (l + r) / 2.0;
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &point[i].x, &point[i].y, &point[i].z);
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            len[i][j] = len[j][i] = dis(point[i], point[j]);
            cost[i][j] = cost[j][i] = fabs(point[i].z - point[j].z);
        }
    }
    printf("%.3f\n", ratio_mst());
}

int main() {
    while (~scanf("%d", &n) && n) {
        input();
        solve();
    }
    return 0;
}
