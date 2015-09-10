#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 310;
const int MAXP = 110;
int nCase, N, P, from[MAXP];
vector<int> graph[MAXN];
bool used[MAXP];

void init() {
    for (int i = 0; i < MAXN; i++) {
        graph[i].clear();
    }
}

void input() {
    scanf("%d%d", &P, &N);
    for (int i = 1; i <= P; i++) {
        int Count;
        scanf("%d", &Count);
        while (Count--) {
            int s;
            scanf("%d", &s);
            graph[s].push_back(i);
        }
    }
}

bool match(int s) {
    for (int i = 0; i < graph[s].size(); i++) {
        int c = graph[s][i];
        if (!used[c]) {
            used[c] = true;
            if (from[c] == -1 || match(from[c])) {
                from[c] = s;
                return true;
            }
        }
    }
    return false;
}

int hungary() {
    int total = 0;
    memset(from, -1, sizeof(from));
    for (int i = 1; i <= N; i++) {
        memset(used, false, sizeof(used));
        if (match(i)) {
            total++;
        }
    }
    return total;
}

void solve() {
    if (hungary() == P) {
        printf("YES\n");
    } else {
        printf("NO\n");
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
