#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 10;
const int MAXM = 1000000;
const int INF = 0x3f3f3f3f;

int id[10010], v[MAXN], n, nCase, cnt;
vector<int> vv;
int step[MAXN][MAXM];
bool visited[MAXM];

void bfs(int n) {
    queue<int> q;
    memset(visited, false, sizeof(visited));

    int target = 0;
    for (int i = 0; i < n; i++) {
        target *= n;
        target += i;
    }
    q.push(target);
    visited[target] = true;
    step[n][target] = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        int st[MAXN];
        memset(st, 0x3f, sizeof(st));
        int t = cur;
        for (int i = n-1; i >= 0; i--) {
            int x = t % (n);
            t /= (n);
            id[i] = x;
            st[x] = i;
        }

        for (int i = 0; i < n; i++) {
            if (st[i] == INF) continue;

            int cur_id = id[st[i]];

            if (i > 0 && (st[i-1] == INF || st[i] < st[i-1])) {
                id[st[i]] = i - 1;

                int s = 0;
                for (int i = 0; i < n; i++) {
                    s *= (n);
                    s += id[i];
                }

                if (!visited[s]) {
                    visited[s] = true;
                    step[n][s] = step[n][cur] + 1;
                    q.push(s);
                }

                id[st[i]] = cur_id;
            }

            if (i < n-1 && (st[i+1] == INF || st[i] < st[i+1])) {
                id[st[i]] = i + 1;

                int s = 0;
                for (int i = 0; i < n; i++) {
                    s *= (n);
                    s += id[i];
                }
                if (!visited[s]) {
                    visited[s] = true;
                    step[n][s] = step[n][cur] + 1;
                    q.push(s);
                }

                id[st[i]] = cur_id;
            }
        }
    }
}

void init() {
    vv.clear();
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        vv.push_back(v[i]);
    }
    sort(vv.begin(), vv.end());
    for (int i = 0; i < n; i++) {
        id[vv[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        v[i] = id[v[i]];
    }
    for (int i = 0; i < n; i++) {
        id[v[i]] = i;
    }

    int s = 0;
    for (int i = 0; i < n; i++) {
        s *= (n);
        s += id[i];
    }

    printf("%d\n", step[n][s]);
}

int main() {
    memset(step, -1, sizeof(step));
    for (int i = 1; i <= 7; i++) {
        bfs(i);
    }

    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
