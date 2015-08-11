#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int MAXN = 20;
const int INF = 0x3f3f3f3f;

int nCase, n, graph[MAXN][MAXN], sum[MAXN], ans, Ans;
bool visitedR[MAXN], visitedXY[MAXN*2], visitedYX[MAXN*2];
int uu;
void init() {
//    memset(visitedR, false, sizeof(visitedR));
//    memset(visitedXY, false, sizeof(visitedXY));
//    memset(visitedYX, false, sizeof(visitedYX));
    for (int i = 0; i < MAXN; i++) {
        visitedR[i] = false;
        visitedXY[i] = visitedXY[i+n] = false;
        visitedYX[i] = visitedYX[i+n] = false;
    }
    ans = Ans = 0;
    uu = 0;
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
}

void dfs(int x) {
    //cout << x << endl;
    uu++;
    if(uu > 600000) return;
    if (x == -1) {
        Ans = max(Ans, ans);
        //cout << "!!!" << endl;
        return;
    }

    if (ans + sum[x+1] <= Ans) return;

    for (int y = n-1; y >= 0; y--) {
        if (!visitedR[y]) {
            if (!visitedXY[x+y]) {
                if (!visitedYX[x-y+n]) {
                    visitedR[y] = true;
                    visitedXY[x+y] = true;
                    visitedYX[x-y+n] = true;
                    ans += graph[x][y];

                    dfs(x-1);

                    ans -= graph[x][y];
                    visitedYX[x-y+n] = false;
                    visitedXY[x+y] = false;
                    visitedR[y] = false;
                }
            }
        }
    }
}

void solve() {
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + graph[i-1][n-1];
    }

    dfs(n-1);
    printf("%d\n", Ans);
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
