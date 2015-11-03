#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <set>
using namespace std;

const int MAXK = 310;
const int MAXN = 25;
const int K = 300;

int nCase, cCase, n, m, a[MAXN], b[MAXN], id[MAXN], square[MAXK];
bool visited[MAXK];
long long c[MAXN][MAXN];
set<long long> st;

void init() {
    for (int i = 0; i < MAXK; i++) {
        square[i] = i * i;
    }
}

bool isSquare(int x) {
    int t = sqrt(x);
    if (t * t == x) return true;
    return false;
}

void input() {
    scanf("%d%d", &n, &m);
}

int generateSquare() {
    while (true) {
        int t = rand() % K + 10;
        if (!visited[t]) {
            visited[t] = true;
            return t;
        }
    }
}

bool check() {
    st.clear();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (st.find(c[i][j]) != st.end()) return false;
            st.insert(c[i][j]);
        }
    }
    return true;
}

void solve() {
    while (true) {
        memset(visited, false, sizeof(visited));

        // a
        while (true) {
            bool success = false;

            int sum = 0;
            for (int i = 1; i < n; i++) {
                id[i] = generateSquare();
                a[i] = square[id[i]];
                sum += a[i];
            }
            for (int i = 1; i <= K; i++) {
                if (!visited[i]) {
                    if (isSquare(sum + square[i])) {
                        visited[i] = true;
                        a[n] = square[i];
                        success = true;
                        break;
                    }
                }
            }

            if (success) break;

            for (int i = 1; i < n; i++) {
                visited[id[i]] = false;
            }
        }

        // b
        while (true) {
            bool success = false;

            int sum = 0;
            for (int i = 1; i < m; i++) {
                id[i] = generateSquare();
                b[i] = square[id[i]];
                sum += b[i];
            }
            for (int i = 1; i <= K; i++) {
                if (!visited[i]) {
                    if (isSquare(sum + square[i])) {
                        visited[i] = true;
                        b[m] = square[i];
                        success = true;
                        break;
                    }
                }
            }

            if (success) break;

            for (int i = 1; i < m; i++) {
                visited[id[i]] = false;
            }
        }

        // c
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                c[i][j] = (long long) a[i] * b[j];
            }
        }

        if (check()) break;
    }

    if (++cCase) {
        printf("\n");
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            printf("%lld ", c[i][j]);
        }
        printf("%lld\n", c[i][m]);
    }
}

int main() {
    init();
    srand(time(NULL));

    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
