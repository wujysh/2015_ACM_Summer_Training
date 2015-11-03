#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>
using namespace std;

const int MAXN = 3010;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

long long xx[MAXN], x[MAXN];
long long yy[MAXN], y[MAXN];
long long dist[MAXN][MAXN];
long long dp[MAXN][MAXN][4];
long long t[MAXN];
long long xi, yi, xf, yf;
int n;

struct Node {
    long long x, y, t;
    Node() {}
    Node(long long _y, long long _x, long long _t) : x(_x), y(_y), t(_t) {}
    bool operator < (const Node &b) const {
        return t > b.t;
    }
};

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int pos = 2 * i;
        scanf("%lld%lld%lld%lld%lld", &xx[pos], &yy[pos], &xx[pos + 1], &yy[pos + 1], &t[i]);
        x[pos] = xx[pos];
        x[pos + 1] = xx[pos + 1];
        y[pos] = yy[pos];
        y[pos + 1] = yy[pos + 1];
    }
}

void solve() {
    int nn = 2 * n;
    x[nn] = xi;
    x[nn + 1] = xf;
    y[nn] = yi;
    y[nn + 1] = yf;
    nn += 2;
    sort(x, x + nn);
    sort(y, y + nn);
    long long sz_x = unique(x, x + nn) - x;
    long long sz_y = unique(y, y + nn) - y;
    map<long long, long long> map_x, map_y;
    for (int i = 0; i < sz_x; i++) {
        map_x[x[i]] = i;
    }
    for (int i = 0; i < sz_y; i++) {
        map_y[y[i]] = i;
    }

    for (int i = 0; i <= sz_y; i++) {
        for (int j = 0; j <= sz_x; j++) {
            for (int k = 0; k < 4; k++) {
                dp[i][j][k] = 10;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        int pos = 2 * k;
        long long bi = map_y[yy[pos]], bj = map_x[xx[pos]];
        long long ei = map_y[yy[pos + 1]], ej = map_x[xx[pos + 1]];
        long long time = t[k];
        for (int i = bi + 1; i < ei; i++) {
            for (int j = bj + 1; j < ej; j++) {
                dp[i][j][2] = dp[i - 1][j][0] = time;
                dp[i][j][3] = dp[i][j - 1][1] = time;
            }
        }
        for (int i = bi + 1; i < ei; i++) {
            dp[i][ej][3] = dp[i][ej - 1][1] = time;
        }
        for (int j = bj + 1; j < ej; j++) {
            dp[ei][j][2] = dp[ei - 1][j][0] = time;
        }
    }

    priority_queue<Node> heap;
    memset(dist, 0x3f, sizeof(dist));
    heap.push(Node(map_y[yi], map_x[xi], 0));
    dist[map_y[yi]][map_x[xi]] = 0;
    long long ans = -1;
    while (!heap.empty()) {
        Node cur = heap.top();
        heap.pop();
        if (cur.y == map_y[yf] && cur.x == map_x[xf]) {
            ans = dist[cur.y][cur.x];
            break;
        }
        if (cur.t > dist[cur.y][cur.x]) continue;

        for (int k = 0; k < 4; k++) {
            long long ni = cur.y + dy[k];
            long long nj = cur.x + dx[k];
            if (ni < 0 || nj < 0 || ni >= sz_y || nj >= sz_x) continue;
            long long edge = dp[cur.y][cur.x][k] * (abs(y[ni] - y[cur.y]) + abs(x[nj] - x[cur.x]));
            if (dist[ni][nj] > dist[cur.y][cur.x] + edge) {
                dist[ni][nj] = dist[cur.y][cur.x] + edge;
                heap.push(Node(ni, nj, dist[ni][nj]));
            }
        }
    }
    printf("%lld\n", ans);
}

int main() {
    while (~scanf("%lld%lld%lld%lld", &xi, &yi, &xf, &yf)) {
        input();
        solve();
    }
    return 0;
}
