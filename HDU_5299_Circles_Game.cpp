#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 20010;

struct Circle {
    int x, y, r;
    Circle() {}
    Circle(int _x, int _y, int _r) : x(_x), y(_y), r(_r) {}
    bool operator < (const Circle &b) const {
        return x < b.x;
    }
} circle[MAXN];

int nCase, n, fa[MAXN], nim[MAXN];
vector<int> G[MAXN];

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &circle[i].x, &circle[i].y, &circle[i].r);
    }
}

void init() {
    for (int i = 0; i < n; i++) {
        fa[i] = i;
        G[i].clear();
    }
    memset(nim, -1, sizeof(nim));
}

inline int sqr(int x) {
    return x * x;
}

bool judge(int i, int j) {  // whether circle[i] contains circle[j]
    Circle a = circle[i], b = circle[j];
    return a.r > b.r && sqr(a.x-b.x) + sqr(a.y-b.y) < sqr(a.r);
}

int SG(int u) {
    if (nim[u] != -1) return nim[u];
    int ret = 0;
    for (int i = 0; i < G[u].size(); i++) {
        ret ^= SG(G[u][i]);
    }
    ret += 1;
    return nim[u] = ret;
}

void solve() {
    sort(circle, circle+n);

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n && circle[j].x - circle[i].x <= circle[i].r; j++) {
            if (judge(i, j)) {
                if (fa[j] == j) {
                    fa[j] = i;
                } else {
                    if (circle[i].r < circle[fa[j]].r) {
                        fa[j] = i;
                    }
                }
            }
        }
        for (int j = i-1; j >= 0 && circle[i].x - circle[j].x <= circle[i].r; j--) {
            if (judge(i, j)) {
                if (fa[j] == j) {
                    fa[j] = i;
                } else {
                    if (circle[i].r < circle[fa[j]].r) {
                        fa[j] = i;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (fa[i] != i) {
            G[fa[i]].push_back(i);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (fa[i] == i) {
            ans ^= SG(i);
        }
    }

    if (ans) {
        printf("Alice\n");
    } else {
        printf("Bob\n");
    }
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        init();
        solve();
    }
    return 0;
}
