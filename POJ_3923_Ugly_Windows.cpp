#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 110;

char graph[MAXN][MAXN];
bool ans[26], visited[MAXN][MAXN];
int n, m;

void init() {
    memset(ans, false, sizeof(ans));
    memset(visited, false, sizeof(visited));
}

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%s", graph[i]);
    }
}

bool judge(int x, int y) {
    //cout << x << " " << y << endl;
    int x1 = x, y1 = y, x2 = x, y2 = y;
    for (int j = y+1; j <= m; j++) {  // right
        if (visited[x][j] || graph[x][j] != graph[x][y]) {
            y1 = j - 1;
            break;
        }
        visited[x][j] = true;
    }
    for (int i = x+1; i <= n; i++) {  // down
        if (visited[i][y1] || graph[i][y1] != graph[x][y]) {
            x1 = i - 1;
            break;
        }
        visited[i][y1] = true;
    }

    for (int i = x+1; i <= n; i++) {  // down
        if (visited[i][y] || graph[i][y] != graph[x][y]) {
            x2 = i - 1;
            break;
        }
        visited[i][y] = true;
    }
    for (int j = y+1; j <= m; j++) {  // right
        if (graph[x2][j] != graph[x][y] || (visited[x2][j] && graph[x2][j] != graph[x][y])) {
            y2 = j - 1;
            break;
        }
        visited[x2][j] = true;
    }

    //cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

    if (x1 != x2 || y1 != y2) return false;
    if (x1-x < 2 || y1-y < 2) return false;

    for (int i = x+1; i < x1; i++) {
        for (int j = y+1; j < y1; j++) {
            if (visited[i][j] || graph[i][j] != '.') {
                return false;
            }
            visited[i][j] = true;
        }
    }
    return true;
}

void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && graph[i][j] >= 'A' && graph[i][j] <= 'Z') {
                visited[i][j] = true;
                if (judge(i, j)) {
                    ans[graph[i][j] - 'A'] = true;
                }
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (ans[i]) {
            printf("%c", 'A' + i);
        }
    }
    printf("\n");
}

int main() {
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        if (n < 3 || m < 3) continue;
        init();
        input();
        solve();
    }
    return 0;
}
