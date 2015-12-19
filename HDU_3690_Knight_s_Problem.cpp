#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>
using namespace std;

const int MAXM = 15;
const int K = 3;

struct State {
    int x, y, step;
    State() {}
    State(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}
};
queue<State> q;

int nCase, fx, fy, tx, ty, m, dx[MAXM], dy[MAXM], a, b, c, d;
map<int, map<int, bool> > visited;

template<typename T>
T sqr(T x) {
    return x * x;
}

void input() {
    scanf("%d%d%d%d", &fx, &fy, &tx, &ty);
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &dx[i], &dy[i]);
    }
}

void init() {
    while (!q.empty()) {
        q.pop();
    }
    visited.clear();

    a = ty - fy;
    b = fx - tx;
    c = fx * (fy - ty) + fy * (tx - fx);
    d = 0;
    for (int i = 0; i < m; i++) {
        d = max(d, sqr(dx[i]) + sqr(dy[i]));
    }
}

bool isValid(int x, int y) {
    if (sqr(x - fx) + sqr(y - fy) <= sqr(K) * d) return true;
    if (sqr(x - tx) + sqr(y - ty) <= sqr(K) * d) return true;
    if ((tx - fx) * (x - fx) + (ty - fy) * (y - fy) < 0) return false;
    if ((fx - tx) * (x - tx) + (fy - ty) * (y - ty) < 0) return false;
    if (sqr((long long) a*x + b*y + c) <= (long long) d * (sqr(a) + sqr(b))) return true;
    return false;
}

void solve() {
    q.push(State(fx, fy, 0));
    visited[fx][fy] = true;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.x == tx && cur.y == ty) {
            printf("%d\n", cur.step);
            return;
        }

        for (int i = 0; i < m; i++) {
            int nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (isValid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push(State(nx, ny, cur.step+1));
            }
        }
    }

    printf("IMPOSSIBLE\n");
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
