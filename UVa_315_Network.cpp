#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 110;

vector<int> G[MAXN];
int N, low[MAXN], dfn[MAXN], vis[MAXN], ans;
bool cut[MAXN];  // bridge[MAXN][MAXN];

void init() {
    for (int i = 1; i <= N; i++) {
        G[i].clear();
    }
    memset(vis, 0, sizeof(vis));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(cut, false, sizeof(cut));
//    memset(bridge, false, sizeof(bridge));
    ans = 0;
}

void input() {
    string line;
    getline(cin, line);
    while (getline(cin, line) && line != "0") {
        stringstream ss(line);
        int u, v;
        ss >> u;
        while (ss >> v) {
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
}

void cut_bridge(int cur, int father, int dep) {
    vis[cur] = 1;
    dfn[cur] = low[cur] = dep;
    int children = 0;
    for (int i = 0; i < G[cur].size(); i++) {
        int v = G[cur][i];
        if (v != father && vis[v] == 1) {
            low[cur] = min(low[cur], dfn[v]);
        } else if (vis[v] == 0) {
            cut_bridge(v, cur, dep+1);
            children++;
            low[cur] = min(low[cur], low[v]);
            if ((father == -1 && children > 1) || (father != -1 && low[v] >= dfn[cur])) {
                cut[cur] = true;
            }
//            if (low[v] > dfn[cur]) {
//                bridge[cur][v] = bridge[v][cur] = true;
//            }
        }
    }
    vis[cur] = 2;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        if (vis[i] == 0) {
            cut_bridge(i, -1, 0);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (cut[i]) {
            ans++;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> N && N) {
        init();
        input();
        solve();
    }
    return 0;
}
