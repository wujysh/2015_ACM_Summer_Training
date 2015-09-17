#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 10010;

vector<int> G[MAXN];
bool visited[MAXN];
int nCase, m, p, v[MAXN], cnt, inDegree[MAXN];
long long ans;

void init() {
    for (int i = 0; i < MAXN; i++) {
        G[i].clear();
        inDegree[i] = 0;
    }
    ans = 0;
}

void input() {
    scanf("%d%d", &p, &m);
    for (int i = 1; i <= p; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
        inDegree[b]++;
        G[b].push_back(a);
        inDegree[a]++;
    }
}

long long dfs(int u) {
    long long ret = v[u];
    for (int i = 0; i < G[u].size(); i++) {
        int vv = G[u][i];
        if (!visited[vv]) {
            visited[vv] = true;
            cnt++;
            ret += dfs(vv);
        }
    }
    return ret;
}

void solve() {
    queue<int> q;
    for (int i = 1; i <= p; i++) {
        if (inDegree[i] < 2) {
            visited[i] = true;
            q.push(i);
        } else {
            visited[i] = false;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < G[u].size(); i++) {
            int vv = G[u][i];
            inDegree[vv]--;
            if (!visited[vv] && inDegree[vv] < 2) {
                visited[vv] = true;
                q.push(vv);
            }
        }
    }

    for (int i = 1; i <= p; i++) {
        if (!visited[i]) {
            visited[i] = true;
            cnt = 1;
            long long t = dfs(i);
            if (cnt % 2 == 1) {
                ans += t;
            }
        }
    }
    printf("%I64d\n", ans);
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
