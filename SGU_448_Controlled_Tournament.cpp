#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 16;

vector<int> R[MAXN];
int dp[MAXN][20][1 << MAXN], ones[1 << MAXN];
int n, winner;

int DP(int rt, int h, int S) {
    if (ones[S] == 1) return 1;
    if ((1 << h) < ones[S]) return 0;
    if (dp[rt][h][S] != -1) return dp[rt][h][S];

    dp[rt][h][S] = 0;

    for (int S1 = S & (S - 1); S1; S1 = S & (S1 - 1)) {
        if ((S1 >> rt) & 1) {
            int S2 = S1 ^ S;
            for (int i = 0; i < R[rt].size(); i++) {
                int other = R[rt][i];
                if ((S2 >> other) & 1) {
                    dp[rt][h][S] += DP(rt, h-1, S1) * DP(other, h-1, S2);
                }
            }
        }
    }
    return dp[rt][h][S];
}

void init() {
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < MAXN; i++) {
        R[i].clear();
    }
}

void input() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int t;
            scanf("%d", &t);
            if (t) {
                R[i].push_back(j);
            }
        }
    }
}

void solve() {
    int height = ceil(log(n) / log(2));
    printf("%d\n", DP(winner-1, height, (1 << n) - 1));
}

int main() {
    for (int i = 0; i < (1 << MAXN) - 1; i++) {
        ones[i] = ones[i >> 1] + (i & 1);
    }

    while (~scanf("%d%d", &n, &winner)) {
        init();
        input();
        solve();
    }
    return 0;
}

/*
2 1
0 1
0 0
2 1
0 0
1 0
3 3
0 1 1
0 0 1
0 0 0
3 3
0 1 0
0 0 0
1 1 0
3 1
0 1 0
0 0 0
1 1 0
3 3
0 1 0
0 0 1
1 0 0
4 1
0 0 0 1
1 0 0 1
1 1 0 0
0 0 1 0
6 4
0 0 0 0 0 1
1 0 1 0 1 0
1 0 0 1 1 0
1 1 0 0 1 0
1 0 0 0 0 0
0 1 1 1 1 0
7 2
0 1 0 0 0 1 0
0 0 1 0 1 1 1
1 0 0 1 1 0 0
1 1 0 0 0 1 0
1 0 0 1 0 0 1
0 0 1 0 1 0 0
1 0 1 1 0 1 0
8 6
0 0 0 0 1 0 0 0
1 0 1 1 0 0 0 0
1 0 0 0 1 0 0 0
1 0 1 0 0 1 0 1
0 1 0 1 0 0 1 0
1 1 1 0 1 0 0 1
1 1 1 1 0 1 0 0
1 1 1 0 1 0 1 0
*/
