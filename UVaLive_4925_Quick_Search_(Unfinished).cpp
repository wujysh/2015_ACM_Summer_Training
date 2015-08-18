#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 15;
const int MAXM = (1 << 10) + 10;
const int INF = 0x3f3f3f3f;

int s, n, p, dp[MAXN][MAXM];
bool graph[MAXN][MAXN];

struct Node {
    int cost, state;
    Node() {}
    Node(int _cost, int _state) : cost(_cost), state(_state) {}
};
vector<Node> v;

void init() {
    memset(graph, false, sizeof(graph));
    memset(dp, 0x3f, sizeof(dp));
    v.clear();
}

void input() {
    scanf("%d%d", &n, &p);
    while (p--) {
        char path[5];
        scanf("%s", path);
        int x = path[0] - 'A' + 1, y = path[1] - 'A' + 1;
        graph[x][y] = graph[y][x] = true;
    }
}

int calcW(int state) {

    return 0;
}

void solve() {
    for (int i = 0; i < (1 << n); i++) {
        int w = calcW(i);
        if (w != INF) {
            v.push_back(Node(w, i));
        }
        dp[0][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < v.size(); j++) {
            for (int k = 0; k < (1 << n); k++) {
                dp[i][k | v[j].state] = min(dp[i][j], dp[i-1][k] + v[j].cost);
            }
        }
    }

    printf("%d\n", dp[n][(1<<n)-1]);
}

int main() {
    while (~scanf("%d", &s) && s) {
        init();
        input();
        solve();
    }
    return 0;
}
