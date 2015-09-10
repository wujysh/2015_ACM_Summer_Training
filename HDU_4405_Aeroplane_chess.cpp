#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 100010;
int N, M, fly[MAXN];
double dp[MAXN];
bool visited[MAXN];

void init() {
    memset(fly, -1, sizeof(fly));
    memset(visited, false, sizeof(visited));
}

void input() {
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        fly[x] = y;
    }
}

double DP(int from) {
    if (from >= N) return dp[from] = 0;
    if (visited[from]) return dp[from];
    visited[from] = true;
    if (fly[from] != -1) {
        return dp[from] = DP(fly[from]);
    } else {
        dp[from] = 0;
        for (int i = 1; i <= 6; i++) {
            dp[from] += 1.0 / 6.0 * (DP(from+i) + 1);
        }
        return dp[from];
    }
}

void output() {
    dp[N] = 0;
    for (int i = N-1; i >= 0; i--) {
        if (fly[i] != -1) {
            dp[i] = dp[fly[i]];
        } else {
            dp[i] = 0.0;
            for (int j = 1; j <= 6; j++) {
                if (j+i <= N) {
                    dp[i] += 1.0 / 6.0 * (dp[j+i] + 1);
                } else {
                    dp[i] += 1.0 / 6.0;
                }
            }
        }
    }
    //printf("%.4lf\n", DP(0));
    printf("%.4lf\n", dp[0]);
}

int main() {
    while (~scanf("%d%d", &N, &M) && (N || M)) {
        init();
        input();
        output();
    }
    return 0;
}
