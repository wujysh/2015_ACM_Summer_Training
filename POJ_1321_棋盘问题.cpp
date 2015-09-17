#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 110;

struct Node {
    int x, y;
    Node() {}
    Node(int _x, int _y) : x(_x), y(_y) {}
} node[MAXN];

int n, k, cnt;
bool visitedX[MAXN], visitedY[MAXN];
char graph[MAXN][MAXN];

void init() {
    cnt = 0;
    memset(visitedX, false, sizeof(visitedX));
    memset(visitedY, false, sizeof(visitedY));
}

void input() {
    getchar();
    for (int i = 0; i < n; i++) {
        scanf("%s", graph[i]);
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == '#') {
                node[++cnt] = Node(i, j);
            }
        }
    }
}

int dfs(int x, int rest) {
    if (rest == 0) return 1;
    if (cnt - x + 1 < rest) return 0;
    if (x > cnt) return 0;

    int ret = 0;

    ret += dfs(x+1, rest);

    if (!visitedX[node[x].x] && !visitedY[node[x].y]) {
        visitedX[node[x].x] = true;
        visitedY[node[x].y] = true;

        ret += dfs(x+1, rest-1);

        visitedX[node[x].x] = false;
        visitedY[node[x].y] = false;
    }

    return ret;
}

void solve() {
    printf("%d\n", dfs(1, k));
}

int main() {
    while (~scanf("%d%d", &n, &k) && !(n == -1 && k == -1)) {
        init();
        input();
        solve();
    }
    return 0;
}
