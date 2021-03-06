#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 110;
const int INF = 0x3f3f3f3f;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};
int N, n, D, nCase;
int num[MAXN], a[MAXN][MAXN], row, col, ans[MAXN], temp[MAXN], res;

void dfs(int u) {
    if (u == n) {
        for (int i = 0; i < n; i++) {
            temp[i] = ans[i];
        }
        for (int i = row - 1; i >= 0; i--) {
            int rr = a[i][n];
            for (int j = i + 1; j < n; j++) {
                rr = (rr ^ (a[i][j] && temp[j]));
            }
            temp[i] = rr;
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += temp[i];
        }
        if (sum < res) {
            res = sum;
        }
    } else {
        ans[u] = 0;
        dfs(u + 1);
        ans[u] = 1;
        dfs(u + 1);
    }
}

int Gauss() {
    row = col = 0;
    for ( ; row < n && col < n; row++, col++) {
        int max_r = row;
        for (int i = row + 1; i < n; i++) {
            if (a[max_r][col] < a[i][col]) {
                max_r = i;
            }
        }
        if (max_r != row) {
            for (int j = col; j <= n; j++) {
                swap(a[row][j], a[max_r][j]);
            }
        }
        if (a[row][col] == 0) {
            row--;
            continue;
        }
        for (int i = row + 1; i < n; i++) {
            if (a[i][col]) {
                for (int j = col; j <= n; j++) {
                    a[i][j] = (a[i][j] ^ a[row][j]);
                }
            }
        }
    }
    for (int i = row; i < n; i++) {
        if (a[i][n] != 0) {
            return -1;
        }
    }
    res = INF;
    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < n; i++) { //将每一行的主元素化成非零
        if (a[i][i]) continue;
        int j;
        for (j = i + 1; j < n; j++) {
            if (a[i][j]) break;
        }
        if (j == n) break;
        for (int k = 0; k < n; k++) {
            swap(a[k][i], a[k][j]);
        }
    }
    dfs(row);
    return res;
}

void init() {
    memset(a, 0, sizeof(a));
    res = MAXN;
}

void input() {
    scanf("%d", &N);
    getchar();
    for (int i = 0; i < N; i++) {
        char graph[MAXN];
        scanf("%s", graph);
        for (int j = 0; j < N; j++) {
            if (graph[j] == 'w') {
                a[i*N+j][N*N] = 1;
            } else {
                a[i*N+j][N*N] = 0;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i*N+j][i*N+j] = 1;
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
                a[nx*N+ny][i*N+j] = 1;
            }
        }
    }
}

void solve() {
    n = N*N;
    int ans = Gauss();
    if (ans == -1) {
        printf("inf\n");
    } else {
        printf("%d\n", ans);
    }
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
