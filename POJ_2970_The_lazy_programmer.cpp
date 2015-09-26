#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 110000;

struct Node {
    int a, b, d;
    double x;
    bool operator < (const Node& x) const {
        return a < x.a;
    }
} e[MAXN];

bool cmp(const Node x, const Node y) {
    return x.d < y.d;
}

priority_queue<Node> q;
int n;

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].d);
        e[i].x = 0;
    }
    e[0].d = 0;
}

void solve() {
    sort(e + 1, e + n + 1, cmp);

    double ans = 0;
    double sum = 0;
    for (int i = 1; i <= n; i++) {
        q.push(e[i]);
        sum += e[i].b;
        if (sum > e[i].d) {
            while (sum > e[i].d) {
                Node cur = q.top();
                q.pop();
                double z = (double)(sum - e[i].d) / cur.a;
                if ((double)cur.b / cur.a - cur.x > z) {
                    cur.x += z;
                    ans += z;
                    sum -= z * cur.a;
                    q.push(cur);
                } else {
                    z = (double)cur.b / cur.a - cur.x;
                    sum -= z * cur.a;
                    ans += z;
                    cur.x += z;
                }
            }
        }
    }

    while (!q.empty()) {
        q.pop();
    }

    printf("%.2f\n", ans);
}

int main() {
    while (~scanf("%d", &n)) {
        input();
        solve();
    }
    return 0;
}
