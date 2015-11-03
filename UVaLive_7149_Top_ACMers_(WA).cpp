#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100010;

vector<int> G[MAXN];
int nCase, cCase, n, m, inDegree[MAXN], ans;

void init() {
    for (int i = 0; i < MAXN; i++) {
        G[i].clear();
        inDegree[i] = 0;
    }
}

void input() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        G[b].push_back(a);
        inDegree[a]++;
    }
}

void solve() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    ans = q.size() - 1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        int cnt = 0;
        for (int i = 0; i < G[cur].size(); i++) {
            int v = G[cur][i];
            if (--inDegree[v] == 0) {
                q.push(v);
                cnt++;
            }
        }
        if (cnt > 1) {
            ans += cnt - 1;
        }
    }

    printf("Case #%d: %d\n", ++cCase, ans);
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
