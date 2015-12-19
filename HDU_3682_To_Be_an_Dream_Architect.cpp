#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1010;
const int MAXM = 1010;

bool visited[MAXN][MAXN], vis[MAXN][MAXN];
int n, m, nCase, ans;
vector<pair<char, int> > v[MAXN];

void init() {
    memset(visited, false, sizeof(visited));
    ans = 0;
    for (int i = 0; i < MAXN; i++) {
        v[i].clear();
    }
}

void input() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        char axis1, axis2;
        int a, b;
        getchar();
        scanf("%c=%d,%c=%d", &axis1, &a, &axis2, &b);

        if (a < 1 || a > n || b < 1 || b > n) continue;

        if (axis1 == 'X' && axis2 == 'Y') {
            if (!visited[a][b]) {
                visited[a][b] = true;
                ans += n;
            }
        } else if (axis1 == 'Y' && axis2 == 'X') {
            if (!visited[b][a]) {
                visited[b][a] = true;
                ans += n;
            }
        } else if (axis1 == 'Z') {
            if (axis2 == 'X') {
                v[a].push_back(make_pair('X', b));
            } else if (axis2 == 'Y') {
                v[a].push_back(make_pair('Y', b));
            }
        } else if (axis2 == 'Z') {
            if (axis1 == 'X') {
                v[b].push_back(make_pair('X', a));
            } else if (axis1 == 'Y') {
                v[b].push_back(make_pair('Y', a));
            }
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        memcpy(vis, visited, sizeof(vis));

        for (int j = 0; j < v[i].size(); j++) {
            pair<char, int> vx = v[i][j];
            if (vx.first == 'X') {
                for (int k = 1; k <= n; k++) {
                    if (!vis[vx.second][k]) {
                        vis[vx.second][k] = true;
                        ans++;
                    }
                }
            } else if (vx.first == 'Y') {
                for (int k = 1; k <= n; k++) {
                    if (!vis[k][vx.second]) {
                        vis[k][vx.second] = true;
                        ans++;
                    }
                }
            }
        }
    }

    printf("%d\n", ans);
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
